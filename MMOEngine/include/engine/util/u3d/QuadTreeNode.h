/*
 Copyright (C) 2007 <SWGEmu>. All rights reserved.
 Distribution of this file for usage outside of Core3 is prohibited.
 */

#ifndef QUADTREENODE_H_
#define QUADTREENODE_H_

/*
 Quad tree interface
 Copyright (C) 2003 by The Arianne Team
 Copyright (C) 2005 Team OpenWoW
 Copyright (C) 2006 Team SWGEmu

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "system/lang.h"

//#ifdef WITH_STM
#include "engine/stm/TransactionalReference.h"
//#endif

/**
 * A quad tree is a 2D data structure that keeps lots of objects nicely
 * sorted in a tree with four children in every node, so that queries like
 * "give me a list of objects that are near the point X,Y" works lighting
 * fast.
 */

namespace engine {
namespace util {
namespace u3d {

class QuadTreeEntry;

class QuadTreeNode: public Object {
	SortedVector<ManagedReference<engine::util::u3d::QuadTreeEntry*> > objects;

//#ifdef WITH_STM
	TransactionalWeakReference<QuadTreeNode*> parentNode;
	TransactionalReference<QuadTreeNode*> nwNode;
	TransactionalReference<QuadTreeNode*> neNode;
	TransactionalReference<QuadTreeNode*> swNode;
	TransactionalReference<QuadTreeNode*> seNode;
//#else
/*	Reference<QuadTreeNode*> parentNode;
	Reference<QuadTreeNode*> nwNode;
	Reference<QuadTreeNode*> neNode;
	Reference<QuadTreeNode*> swNode;
	Reference<QuadTreeNode*> seNode;*/
//#endif

	float minX, minY;
	float maxX, maxY;

	float dividerX, dividerY;

public:
	QuadTreeNode();
	QuadTreeNode(float minx, float miny, float maxx, float maxy,
			QuadTreeNode *parent);

	~QuadTreeNode();

	Object* clone() {
		return ObjectCloner<QuadTreeNode>::clone(this);
	}

	Object* clone(void* object) {
		return TransactionalObjectCloner<QuadTreeNode>::clone(this);
	}

	void free() {
		TransactionalMemoryManager::instance()->destroy(this);
	}

	// Add a object to this node
	void addObject(QuadTreeEntry *obj);

	QuadTreeEntry* getObject(int index) {
		return objects.get(index);
	}

	// Remove a object by GUID
	void removeObject(QuadTreeEntry *obj);

	void removeObject(int index);

	// Approximative test if a circle with center in x,y and
	// given radius crosses this node.
	bool testInRange(float x, float y, float range);

	// Check if this node makes any sense to exist
	void check();

	bool validateNode() {
		if (minX > maxX || minY > maxY/* || objects.size() > 1000*/)
			return false;
		else
			return true;
	}

	// Check if this node has any associated objects
	inline bool isEmpty() {
		return objects.isEmpty();
	}

	// Check if this node has children nodes
	inline bool hasSubNodes() {
		return nwNode != NULL || neNode != NULL || swNode != NULL || seNode
				!= NULL;
	}

	// Test if the point is inside this node
	inline bool testInside(float x, float y) const {
		return x >= minX && x < maxX && y >= minY && y < maxY;
	}

	// Test if the object is inside this node
	bool testInside(QuadTreeEntry* obj) const;

	String toStringData();

	friend class QuadTree;
	friend class QuadTreeEntryImplementation;
};

} // u3d
} // namespace util
} // namespace engine

using namespace engine::util::u3d;

#endif /*QUADTREENODE_H_*/
