#ifndef __ALEMBIC_RECURSIVE_IMPORTER_H__
#define __ALEMBIC_RECURSIVE_IMPORTER_H__

#include "AlembicDefinitions.h"

class progressUpdate
{
public:
	progressUpdate(int total):i(GET_MAX_INTERFACE()), interval(0), total(total)
	{
	
	}

	MAXInterface *i;
	int interval;
	int total;

	void increment()
	{
		interval++;
	}

	void update()
	{
		if( ( interval % 10 ) == 0 ) {	
			double dbProgress = ((double)interval) / total;
			i->ProgressUpdate(static_cast<int>(100 * dbProgress));
		}
	}
};

enum nodeCategory{
	NODECAT_GEOMETRY,
	NODECAT_XFORM,
	NODECAT_UNSUPPORTED
};

nodeCategory getNodeCategory(Alembic::AbcGeom::IObject& iObj);

int recurseOnAlembicObject(Alembic::AbcGeom::IObject& iObj, INode *pParentMaxNode, 
						   bool bNodeWasMerged, alembic_importoptions &options, std::string& file, progressUpdate& progress);

#endif