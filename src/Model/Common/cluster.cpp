#include "cluster.h"

#include "utils/logger.h"
#include "utils/file_system.h"
#include "utils/containers/converters.h"

#include <float.h>

CREATE_LOGGER("Cluster");

Cluster::Cluster(const utils::String &cluster_name, const utils::String &pc_name, const utils::String &datetime_clustered)
  : m_cluster_name(cluster_name)
  , m_pc_name(pc_name)
  , m_datetime_clustered(datetime_clustered)
{
  cluster_maxs.x = FLT_MIN; cluster_maxs.y = FLT_MIN; cluster_maxs.z = FLT_MIN;
  cluster_mins.x = FLT_MAX; cluster_mins.y = FLT_MAX; cluster_mins.z = FLT_MAX;
}

Cluster::Cluster(const utils::String &path)
  : m_cluster_name("")
  , m_pc_name("")
  , m_datetime_clustered("")
{
  cluster_maxs.x = FLT_MIN; cluster_maxs.y = FLT_MIN; cluster_maxs.z = FLT_MIN;
  cluster_mins.x = FLT_MAX; cluster_mins.y = FLT_MAX; cluster_mins.z = FLT_MAX;
  LoadFrom(path);
}

const utils::String &Cluster::GetClusterName() const
{
  return m_cluster_name;
}

const utils::String &Cluster::GetPCName() const
{
  return m_pc_name;
}

const utils::String &Cluster::GetDateTimeClustered() const
{
  return m_datetime_clustered;
}

void Cluster::SaveTo(const utils::String &path) const
{
  using namespace utils::file_system;
  utils::String filename = m_pc_name + "/" + m_datetime_clustered + "_" + m_cluster_name + ".cluster";

  if(File::IsExists(path + filename))
  {
    LOG_INFO("Cluster " << path + filename << " already exists");
    return;
  }
  LOG_DEBUG("Saving new cluster : " << path + filename);

  File file(path + filename);
  file.Open(File::OpenMode::Write);
  if(file.IsOpened())
  {
//    for(auto point : *this)
//    {
//      file.WriteLine(point.ToString());
//    }
    file.Close();
  }
}

void Cluster::LoadFrom(const utils::String &path)
{
  LOG_AUTO_TRACE();
  utils::file_system::File file(path);
  LoadFrom(file);
}

void Cluster::LoadFrom(utils::file_system::File& file)
{
  LOG_AUTO_TRACE();
  using namespace utils;
  file.Open(file_system::File::OpenMode::Read);

  if(!file.IsOpened())
  {
    LOG_ERROR("Cant open " << file.GetFullPath());
    return;
  }

  String filename = file_system::File::GetFileName(file.GetFullPath());
  Vector<String> filename_parts = SplitCSV(filename, "_");
  m_datetime_clustered = filename_parts[0];
  m_cluster_name = filename_parts[1];

  String directory = file_system::File::GetDirectory(file.GetFullPath());
  m_pc_name = directory.substr(directory.find_last_of('/') + 1);

  utils::String line;
//  do
//  {
//    line = file.ReadLine();
//    AddPoint(utils::convertTo<utils::positions::Location3>(line));
//  } while(!line.empty());

//  file.Close();
  //  LOG_DEBUG("Loaded " << size() << " points from " << file.GetFullPath());
}

void Cluster::OnPointAppended(PointCloud::PointType &p)
{
  if(p.x > cluster_maxs.x) cluster_maxs.x = p.x;
  if(p.y > cluster_maxs.y) cluster_maxs.y = p.y;
  if(p.z > cluster_maxs.z) cluster_maxs.z = p.z;
  if(p.x < cluster_mins.x) cluster_mins.x = p.x;
  if(p.y < cluster_mins.y) cluster_mins.y = p.y;
  if(p.z < cluster_mins.z) cluster_mins.z = p.z;
}
