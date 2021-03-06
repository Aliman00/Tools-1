/** -*-c++-*-
 *  \file   swgRepository.hpp
 *  \author Kenneth R. Sewell III

 Visualization of SWG data files.
 Copyright (C) 2009 Kenneth R. Sewell III

 This file is part of swgOSG.

 swgOSG is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 swgOSG is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with swgOSG; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <iostream>
#include <string>
#include <map>
#include <memory>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LOD>
#include <osg/Material>
#include <osg/Math>
#include <osg/MatrixTransform>
#include <osg/Node>
#include <osg/StateSet>
#include <osg/Texture2D>

#include <osgAnimation/Bone>
#include <osgAnimation/Skeleton>
//#include <osgAnimation/RigGeometry>
#include <osgAnimation/RigTransformSoftware>
#include <osgAnimation/BasicAnimationManager>
#include <OpenThreads/ReentrantMutex>
#include <OpenThreads/ScopedLock>

#include <osgDB/ReaderWriter>
#include <boost/shared_ptr.hpp>
#include <treLib/treArchive.hpp>

#ifndef SWGREPOSITORY_HPP
#define SWGREPOSITORY_HPP

class swgRepository 
{
public:
  swgRepository( const std::string &archiveFilePath );
  ~swgRepository();

  osg::ref_ptr< osg::StateSet > loadShader( const std::string &shaderFilename );
  osg::ref_ptr< osg::Node > loadAPT( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadCMP( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadLOD( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadINLY( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadMSH( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadMLOD( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadPRTO( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadSBOT( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadSKMG( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadSTAT( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadSMAT( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadSTOT( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadSCOT( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadTRN( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadWSNP( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osg::Node > loadCLDF( boost::shared_ptr<std::istream> iffFile );
  osg::ref_ptr< osgAnimation::Skeleton >
  loadSKTM( boost::shared_ptr<std::istream> iffFile );

  osg::ref_ptr< osg::Node > loadFile( const std::string &filename );
  osg::ref_ptr< osg::Texture2D > loadTextureFile( const std::string &filename );
  osg::ref_ptr< osg::Node > findFile( const std::string &filename);

  void cleanCurrentObjects() {
	  OpenThreads::ScopedLock<OpenThreads::ReentrantMutex> locker(mutex);

	  nodeMap.clear();
	  stateMap.clear();
	  materialMap.clear();
	  textureMap.clear();
  }

  void createArchive( const std::string &basePath );

  treArchive* getTreArchive() {
	  return &archive;
  }
  

protected:
  osgDB::ReaderWriter *ddsPlugin;
  treArchive archive;
  std::map< std::string, osg::ref_ptr< osg::Texture2D > > textureMap;
  std::map< std::string, osg::ref_ptr< osg::Material > > materialMap;
  std::map< std::string, osg::ref_ptr< osg::StateSet > > stateMap;
  std::map< std::string, osg::ref_ptr< osg::Node > > nodeMap;
  OpenThreads::ReentrantMutex mutex;

};

#endif
