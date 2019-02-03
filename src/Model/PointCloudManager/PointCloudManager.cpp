#include "PointCloudManager.h"

#include "utils/file_system.h"
#include "utils/logger.h"
#include "utils/containers/converters.h"

#include "Model/Clustering/AlgorithmMST.h"
#include "Model/Clustering/AlgorithmCLOPE.h"

#include "Controller/controller.h"

CREATE_LOGGER("PointCloudManager")

PointCloudManager::PointCloudManager(ApplicationSettings& settings, StatisticsManager& stats_manager)
  : m_settings(settings)
  , m_stats_manager(stats_manager)
{
  LOG_AUTO_TRACE();
  utils::file_system::Directory dir(m_settings.get_working_dir());
  utils::file_system::Directory::FilesList files = dir.GetFilesList(true); // uncomment if needed to reopen already clustered
  for(auto file : files)
  {
    if("pointcloud" == file->GetExt())
    {
      SharedPtr<PointCloud> pc(new PointCloud(""));
      m_point_clouds.push_back(pc);

      pc->LoadFrom(*file);
    }
    else if("cluster" == file->GetExt())
    {
//      SharedPtr<Cluster> cluster = utils::make_shared<Cluster>("");
//      m_clusters.push_back(cluster);

//      cluster->LoadFrom(*file);
    }
  }

  m_clustering_algos.push_back(SharedPtr<ClusteringAlgo>(new AlgorithmCLOPE(m_settings)));
  m_clustering_algos.push_back(SharedPtr<ClusteringAlgo>(new AlgorithmMST(m_settings)));
}

PointCloud::Ptr PointCloudManager::LoadNewCloud(utils::String &sPath)
{
  LOG_AUTO_TRACE();

  const utils::String sFileName = utils::file_system::File::GetFileName(sPath);
  utils::file_system::Directory::RecursiveCreate(utils::file_system::ExtendPath(m_settings.get_working_dir(), sFileName));
//  utils::file_system::File::Copy(sPath, utils::file_system::ExtendPath(m_settings.get_working_dir(), sFileName, sFileName) + ".pointcloud");

  SharedPtr<PointCloud> pc(new PointCloud(""));
  m_point_clouds.push_back(pc);

  pc->LoadFrom(sPath);
  pc->ShiftTo(0,0,0);
  return pc;
}

void PointCloudManager::RunClasteringProcess(PointCloud::Ptr cloud, const utils::String& sAlgo, std::map<utils::String, double> params)
{
  LOG_AUTO_TRACE()
  for(auto clustering_algo : m_clustering_algos)
  {
    if(clustering_algo->GetName() != sAlgo) {LOG_DEBUG(clustering_algo->GetName() + " skipped"); continue;}

    if(!cloud.get())
    {
      LOG_ERROR("cloud empty");
      return;
    }

    if(cloud->IsClustered())
    {
      LOG_ERROR("Cloud " << cloud->GetPCName() << " already clustered.");
      return;
    }

    m_stats_manager.StartMeasurement();
    // just for all measurement set to 0 values in stats on start
    sleep(2);
    clustering_algo->SetParams(params);
    m_clusters = clustering_algo->RunTask(cloud);
    sleep(2);
    m_stats_manager.StopMeasurement();
    m_stats_manager.SaveMeasurementData(utils::file_system::ExtendPath(m_settings.get_working_dir(), cloud->GetPCName(), clustering_algo->GetName()));
//    SaveClusters();

    // already clustered map
    SharedPtr<PointCloud> pc(new PointCloud(cloud->GetPCName() + "_" + clustering_algo->GetName() + "_" + m_stats_manager.GetLastStart()));
    *pc.get() += *cloud.get();
    pc->SetClustered(true);
    m_point_clouds.push_back(pc);
    m_controller->AddCloudToList(pc->GetPCName());

    const utils::String& sPcName = pc->GetPCName();
    std::map<utils::String, PointCloud::Ptr> clusters;
    for(auto point : *pc)
    {
      utils::String sCurrentClusterName = sPcName + "_cluster_" + std::to_string(point.label);
      auto cluster_it = clusters.find(sCurrentClusterName);
      if(clusters.end()==cluster_it)
      {
        clusters[sCurrentClusterName] = SharedPtr<PointCloud>(new PointCloud(sCurrentClusterName));
      }
      cluster_it = clusters.find(sCurrentClusterName);
      cluster_it->second->push_back(point);
    }

    for(auto cluster : clusters)
    {
      m_point_clouds.push_back(cluster.second);
      m_controller->AddCluster(sPcName, cluster.second->GetPCName());
    }

    uncolorAllPoints(cloud);
  }
}

void PointCloudManager::SaveClusters()
{
  LOG_AUTO_TRACE()
  for(auto cluster : m_clusters)
  {
      cluster.SaveTo(m_settings.get_working_dir());
  }
}

const PointCloudManager::PointClouds &PointCloudManager::GetPointClouds() const
{
  return m_point_clouds;
}

const PointCloudManager::Clusters &PointCloudManager::GetClusters() const
{
  return m_clusters;
}

PointCloud::Ptr PointCloudManager::GetMatrix(const utils::String &filename) const
{
  LOG_AUTO_TRACE();

  auto it_pc = std::find_if(m_point_clouds.begin(), m_point_clouds.end(),
               [&filename](SharedPtr<PointCloud> p)
  {
    return filename == p->GetPCName();
  });
  if(m_point_clouds.end() != it_pc)
  {
    return *it_pc;
  }

  if(filename.empty()) LOG_ERROR("cloud name empty");

  return PointCloud::Ptr();

//  auto it_cl = std::find_if(m_clusters.begin(), m_clusters.end(),
//               [&filename](SharedPtr<Cluster> p)
//  {
//    return filename == p->GetPCName();
//  });
//  if(m_clusters.end() != it_cl)
//  {
//    return **it_cl;
//  }
//  return PointCloud();
}

const utils::Vector<utils::String> PointCloudManager::GetCloudNames() const
{
  utils::Vector<utils::String> v;
  for(auto& cloud : m_point_clouds)
  {
    v.push_back(cloud->GetPCName());
  }
//  for(auto& cloud : m_clusters)
//  {
//    v.push_back(cloud.GetClusterName());
//  }
  return v;
}
