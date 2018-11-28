#include "AlgorithmMST.h"

#include <map>
#include <unordered_set>
#include <math.h>

#include "utils/date_time.h"
#include "utils/structures/position.h"

#include "utils/logger.h"

#include <pcl/segmentation/random_walker.h>
#include <pcl/kdtree/kdtree_flann.h>

CREATE_LOGGER("Clustering");

typedef std::multimap<float, std::pair<uint32_t, uint32_t>, std::greater<float> > EdgesType; // from higher to lower dist
typedef std::vector<EdgesType::value_type*> EdgesPtrs;

namespace std
{
template<>
class hash<EdgesType::value_type::second_type> {
public:
  size_t operator()(const EdgesType::value_type::second_type &s) const
  {
    size_t h1 = std::hash<uint32_t>()(s.first);
    size_t h2 = std::hash<uint32_t>()(s.second);
    return h1 ^ ( h2 << 1 );
  }
};
} // namespace std

typedef std::unordered_set<EdgesType::value_type::second_type > HashedEdges;

typedef std::unordered_multimap<uint32_t, uint32_t> HashedEdgeToEdge;
typedef std::pair<HashedEdgeToEdge::iterator, HashedEdgeToEdge::iterator> HashedEdgeToEdgeRange;


AlgorithmMST::AlgorithmMST(const ApplicationSettings &settings)
  : m_settings(settings)
{
}

AlgorithmMST::~AlgorithmMST() {}

//void searchAndAdd(PointCloud::PointType& point, pcl::KdTreeFLANN<PointCloud::PointType>& kdtree, int K, EdgesType& edges, HashedEdges& hashed_edges, uint32_t curr_ind, int& added, int duplicates)
//{
//  std::vector<int> pointIdxNKNSearch(K + duplicates);
//  std::vector<float> pointNKNSquaredDistance(K + duplicates);

//  if ( kdtree.nearestKSearch (point, K + duplicates, pointIdxNKNSearch, pointNKNSquaredDistance) > 0 )
//  {
//    for(size_t i = 1; i < pointIdxNKNSearch.size(); ++i) // start from 1 because used point founds itself as nearests
//    {
//      auto existent = hashed_edges.find({pointIdxNKNSearch[i], curr_ind});
//      if(existent == hashed_edges.end())
//      {
//        hashed_edges.emplace(curr_ind, pointIdxNKNSearch[i]);
//        edges.emplace(EdgesType::value_type(pointNKNSquaredDistance[i], {curr_ind, pointIdxNKNSearch[i]}));
//        if(++added == K) return;
//      }
//      else
//      {
//        ++duplicates;
//      }
//    }
//    searchAndAdd(point, kdtree, K, edges, hashed_edges, curr_ind, added, duplicates);
//  }
//}

void linkNeighbors(PointCloud::Ptr& pc, pcl::KdTreeFLANN<PointCloud::PointType>& kdtree, EdgesType& edges, PointCloud::PointType& point, uint32_t curr_index,  const uint32_t& label, const uint32_t neighbors_count, const uint32_t real_neighbors_count, int deep, int clusters_count)
{
//  LOG_TRACE(point << "|" << curr_index << " " << label << " " << neighbors_count << " deep " << deep);
//  if(deep > (pc->points.size() / clusters_count)) return;
  std::vector<int> pointIdxNKNSearch(neighbors_count);
  std::vector<float> pointNKNSquaredDistance(neighbors_count);

  if ( kdtree.nearestKSearch (point, neighbors_count, pointIdxNKNSearch, pointNKNSquaredDistance) > 0 )
  {
    bool any_created = false;
    for(int i = 1; i < pointIdxNKNSearch.size(); ++i)
    {
      PointCloud::PointType& neigh_point = pc->points[pointIdxNKNSearch[i]];
      if(neigh_point.label != label)
      {
        neigh_point.label = label;
        edges.emplace(EdgesType::value_type(pointNKNSquaredDistance[i], {curr_index, pointIdxNKNSearch[i]}));
        linkNeighbors(pc, kdtree, edges, neigh_point, pointIdxNKNSearch[i], label, real_neighbors_count, real_neighbors_count, deep+1, clusters_count);
        any_created = true;
      }
    }
    pointIdxNKNSearch.clear();
    pointNKNSquaredDistance.clear();
    if(!any_created && neighbors_count < pc->points.size())
    {
//      LOG_TRACE("Neighbors multiplied to " << neighbors_count * 2);
      linkNeighbors(pc, kdtree, edges, point, curr_index, label, neighbors_count * 2, real_neighbors_count, deep+1, clusters_count);
    }
  }
}

void generateBones(PointCloud::Ptr pc, EdgesType& edges, int K, int clusters_count)
{
  pcl::KdTreeFLANN<PointCloud::PointType> kdtree;
  kdtree.setInputCloud (pc);

  LOG_TRACE("Trying to find " << K << " neighbors for every point");

//  HashedEdges hashed_edges;
  PointCloud::PointType& start_point = pc->points[0];
  const uint32_t label = 666;
  start_point.label = label;

  linkNeighbors(pc, kdtree, edges, start_point, 0, label, K, K, 0, clusters_count);

  for(auto& point : *pc)
  {
    point.label = 0;
  }

//  uint32_t curr_ind = 0;
//  for(auto& point : *pc)
//  {
//    int added = 0;
//    searchAndAdd(point, kdtree, K, edges, hashed_edges, curr_ind, added, 0);
//    ++curr_ind;
//    if(curr_ind % 100000 == 0) LOG_TRACE("Bones found for : " << curr_ind << ". Bones count = " << edges.size());
//  }
  LOG_TRACE(__FUNCTION__ << " found edges " << edges.size());
}

void markNeighbors(HashedEdgeToEdgeRange& in_neighbors, PointCloud::Ptr pc, EdgesType& edges, HashedEdgeToEdge& e_to_e, uint32_t count_of_runs, uint32_t curr_cluster, uint32_t deep)
{
// if(deep%1000 == 0) LOG_TRACE("Recursion " << count_of_runs << " " << curr_cluster << " " << deep);
//  if(deep > 1000) return;
//  for(auto& in_edge : in_neighbors)
  std::for_each(in_neighbors.first, in_neighbors.second, [&](HashedEdgeToEdge::value_type& v)
  {
    PointCloud::PointType& neighbor_point = pc->points[v.second];
    if(neighbor_point.rgba != count_of_runs) // not processed on current run jet
    {
      neighbor_point.rgba = count_of_runs;
      neighbor_point.label = curr_cluster; // for current run this point in current cluster
      HashedEdgeToEdgeRange* neighbors = new HashedEdgeToEdgeRange(std::move(e_to_e.equal_range(v.second)));

      markNeighbors(*neighbors, pc, edges, e_to_e, count_of_runs, curr_cluster, ++deep);
      delete neighbors;
    }
  });
}

uint32_t markClusters(PointCloud::Ptr pc, EdgesType& edges, uint32_t count_of_runs)
{

  HashedEdgeToEdge EtoE;
  for(auto edge : edges)
  {
    EtoE.emplace(edge.second.first, edge.second.second);
  }

  uint32_t rec_deep = 0;
  uint32_t curr_cluster = 0;
  uint32_t curr_p_ind = 0;
  for(auto& point : *pc)
  {
    if(point.rgba != count_of_runs) // not processed on current run jet
    {
      point.rgba = count_of_runs;
      point.label = curr_cluster; // for current run this point in current cluster
      HashedEdgeToEdgeRange neighbors = EtoE.equal_range(curr_p_ind);
//      EdgesPtrs neighbors;

//      for(EdgesType::value_type& edge : edges)
//      {
//        if(edge.second.first == curr_p_ind)
//        {
//          neighbors.push_back(&edge);
//        }
//      }
//      std::copy_if(edges.begin(), edges.end(), neighbors.end(), [curr_p_ind](EdgesType::value_type& pair){
//        return pair.second.first == curr_p_ind;
//      });
      markNeighbors(neighbors, pc, edges, EtoE, count_of_runs, curr_cluster, ++rec_deep);
      ++curr_cluster;
    }
    ++curr_p_ind;
    if(curr_p_ind % 100000 == 0) LOG_TRACE("Run : " << count_of_runs << " processed : " << curr_p_ind << " clusters : " << curr_cluster);
  }
  return curr_cluster;
}

void removeMaxEdge(EdgesType& edges)
{
  if(edges.size() < 1) return;
  edges.erase(edges.begin());
}

void uncolorAllPoints(PointCloud::Ptr pc)
{
  for(auto& point : *pc)
  {
    point.rgba = UINT32_MAX;
  }
}

utils::Vector<Cluster> AlgorithmMST::RunTask(PointCloud::Ptr pc)
{
  LOG_AUTO_TRACE();
  utils::String date_clustered = utils::date_time::GetDateTimeString("%F_%T");

  EdgesType edges;// from ind to {ind, dist}

  generateBones(pc, edges, m_settings.get_mst_neighbors(), m_settings.get_mst_clusters_count());

  uncolorAllPoints(pc);

  uint32_t runs_count = 0;
  uint32_t clusters_count = markClusters(pc, edges, runs_count);
  while(clusters_count < m_settings.get_mst_clusters_count())
  {
    removeMaxEdge(edges);

    const uint32_t cl_c = clusters_count;
    clusters_count = markClusters(pc, edges, ++runs_count);

    if(cl_c != clusters_count) LOG_TRACE("Found : " << clusters_count << " clusters.");
  }

  LOG_TRACE("Complete. Found : " << clusters_count << " clusters. Runned : " << runs_count << " times.");

  return utils::Vector<Cluster>();
}

utils::String AlgorithmMST::GetName() const
{
  return "MST";
}
