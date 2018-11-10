#include "AlgorithmMST.h"

#include <unordered_map>
#include <math.h>

#include "utils/date_time.h"
#include "utils/structures/position.h"

#include "utils/logger.h"

CREATE_LOGGER("Clustering");


struct Bone
{
  const utils::positions::Location3& from;
  const utils::positions::Location3& to;
  uint64_t dist;
};

typedef std::unordered_map<utils::positions::Location3, Bone> Bones;

using namespace utils::positions;

uint64_t GetDistance(const Location3& l, const Location3& r)
{
  return static_cast<uint64_t>(sqrt(pow(l.x_ - r.x_, 2)+pow(l.y_ - r.y_, 2)+pow(l.z_ - r.z_, 2)));
}

AlgorithmMST::~AlgorithmMST() {}

void GenerateBones(const PointCloud &pc, Bones& bones)
{
  LOG_TRACE(pc.GetPCName());

//  PointCloud::ContainerType::const_iterator begin = pc.begin();
//  PointCloud::ContainerType::const_iterator end = pc.end();
//  for(auto i = begin; i != end; ++i)
//  {
//    for(auto j = begin; j != end; ++j)
//    {
//      if(i == j) continue;

//      uint64_t dist = GetDistance(*i, *j);
//      Bones::iterator it = bones.find(*i);
//      if(bones.end() == it)
//      {
//        bones.insert({*i, {*i, *j, dist}});
//        continue;
//      }

//      if(it->second.dist > dist)
//      {
////        const uint64_t prev_dist = it->second.dist;
//        bones.erase(it);
//        bones.insert({*i, {*i, *j, dist}});
////        LOG_TRACE("Reasigned " << i->ToString() << " -> " << j->ToString() << " : " << prev_dist << " > " << dist);
//      }
//    }
//    LOG_TRACE("processed " << bones.size());
//  }
  LOG_TRACE("Created " << bones.size() << " bones");
}

utils::Vector<utils::SharedPtr<Cluster> > AlgorithmMST::RunTask(const PointCloud &pc)
{
  LOG_AUTO_TRACE();
  utils::String date_clustered = utils::date_time::GetDateTimeString("%F_%T");
  utils::Vector<utils::SharedPtr<Cluster> > clusters;
  Bones bones_map;
  GenerateBones(pc, bones_map);

  return utils::Vector<utils::SharedPtr<Cluster> >();
}

utils::String AlgorithmMST::GetName() const
{
  return "MST";
}
