#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "Foundation.h"

struct SampleInfo
{
   Alembic::AbcCoreAbstract::index_t floorIndex;
   Alembic::AbcCoreAbstract::index_t ceilIndex;
   double alpha;
};

struct ArchiveInfo
{
   std::string path;
};


SampleInfo getSampleInfo(double iFrame,Alembic::AbcCoreAbstract::TimeSamplingPtr iTime, size_t numSamps);
std::string getIdentifierFromRef(const MObject & in_Ref);
MString removeTrailFromName(MString & name);
MString truncateName(const MString & in_Name);
MString injectShapeToName(const MString & in_Name);
MString getFullNameFromRef(const MObject & in_Ref);
MString getFullNameFromIdentifier(std::string in_Identifier);
MObject getRefFromFullName(const MString & in_Path);
MObject getRefFromIdentifier(std::string in_Identifier);
bool isRefAnimated(const MObject & in_Ref);
bool returnIsRefAnimated(const MObject & in_Ref, bool animated);
void clearIsRefAnimatedCache();

// remapping imported names
void nameMapAdd(MString identifier, MString name);
MString nameMapGet(MString identifier);
void nameMapClear();

// utility mappings
MString getTypeFromObject(Alembic::Abc::IObject object);
Alembic::Abc::ICompoundProperty getCompoundFromObject(Alembic::Abc::IObject object);
Alembic::Abc::TimeSamplingPtr getTimeSamplingFromObject(Alembic::Abc::IObject object);
size_t getNumSamplesFromObject(Alembic::Abc::IObject object);

// metadata related
class AlembicObject;
bool SaveMetaData(AlembicObject * obj);

// sortable math objects
class SortableV3f : public Alembic::Abc::V3f
{
public:  
   SortableV3f()
   {
      x = y = z = 0.0f;
   }

   SortableV3f(const Alembic::Abc::V3f & other)
   {
      x = other.x;
      y = other.y;
      z = other.z;
   }
   bool operator < ( const SortableV3f & other) const
   {
      if(other.x != x)
         return other.x > x;
      if(other.y != y)
         return other.y > y;
      return other.z > z;
   }
   bool operator > ( const SortableV3f & other) const
   {
      if(other.x != x)
         return other.x < x;
      if(other.y != y)
         return other.y < y;
      return other.z < z;
   }
   bool operator == ( const SortableV3f & other) const
   {
      if(other.x != x)
         return false;
      if(other.y != y)
         return false;
      return other.z == z;
   }
};

class SortableV2f : public Alembic::Abc::V2f
{
public:  
   SortableV2f()
   {
      x = y = 0.0f;
   }

   SortableV2f(const Alembic::Abc::V2f & other)
   {
      x = other.x;
      y = other.y;
   }
   bool operator < ( const SortableV2f & other) const
   {
      if(other.x != x)
         return other.x > x;
      return other.y > y;
   }
   bool operator > ( const SortableV2f & other) const
   {
      if(other.x != x)
         return other.x < x;
      return other.y < y;
   }
   bool operator == ( const SortableV2f & other) const
   {
      if(other.x != x)
         return false;
      return other.y == y;
   }
};

class AlembicResolvePathCommand : public MPxCommand
{
  public:
    AlembicResolvePathCommand() {}
    virtual ~AlembicResolvePathCommand()  {}

    virtual bool isUndoable() const { return false; }
    MStatus doIt(const MArgList& args);

    static MSyntax createSyntax();
    static void* creator() { return new AlembicResolvePathCommand(); }
};

#endif  // _FOUNDATION_H_
