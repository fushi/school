// File FHgraph.h EXPERIMENT
// Template definitions for FHgraph.  
#ifndef FHGRAPH_H
#define FHGRAPH_H
#include <limits.h>
#include <utility>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <iostream>
using namespace std;

// CostType is some numeric type that expresses cost of edges
// Object is the non-graph data for a vertex
template <class Object, typename CostType>
class FHvertex
{
   // internal typedefs to simplify syntax
   typedef FHvertex<Object, CostType>* VertPtr;
   typedef map<VertPtr, CostType> EdgePairList;

public:
   static int n_sort_key;
   static stack<int> key_stack;
   static enum { SORT_BY_DATA, SORT_BY_DIST } e_sort_type;
   static bool SetNSortType( int which_type );
   static void pushSortKey() { key_stack.push(n_sort_key); }
   static void popSortKey() { n_sort_key = key_stack.top(); key_stack.pop(); };

   static int const INFINITY = INT_MAX;  // defined in limits.h
   EdgePairList adj_list;
   Object data;
   CostType dist;
   VertPtr next_in_path;  // used for client-specific info

   FHvertex( const Object & x = Object() );

   void addToAdjList(VertPtr neighbor, CostType cost);
   bool operator<( const FHvertex<Object, CostType> & rhs) const;
   const FHvertex<Object, CostType> & operator=
      ( const FHvertex<Object, CostType> & rhs);
   void showAdjList();
};

// static const initializations for Vertex --------------
template <class Object, typename CostType>
int FHvertex<Object, CostType>::n_sort_key 
   = FHvertex<Object, CostType>::SORT_BY_DATA;

template <class Object, typename CostType>
stack<int> FHvertex<Object, CostType>::key_stack;
// ------------------------------------------------------

template <class Object, typename CostType>
bool FHvertex<Object, CostType>::SetNSortType( int which_type )
{
   switch (which_type)
   {
   case SORT_BY_DATA:
   case SORT_BY_DIST:
      n_sort_key = which_type;
      return true;
   default:
      return false;
   }
}

template <class Object, typename CostType>
FHvertex<Object, CostType>::FHvertex( const Object & x) 
   : data(x), dist((CostType)INFINITY),
   next_in_path(NULL)
{
   // nothing to do
}

template <class Object, typename CostType>
void FHvertex<Object, CostType>::addToAdjList
   (FHvertex<Object, CostType> *neighbor, CostType cost)
{ 
   adj_list[neighbor] = cost;
}

template <class Object, typename CostType>
bool FHvertex<Object, CostType>::operator<(
   const FHvertex<Object, CostType> & rhs) const
{
   switch (n_sort_key)
   {
   case SORT_BY_DIST:
      return (dist < rhs.dist);
   case SORT_BY_DATA:
      return (data < rhs.data);
   default:
      return false;
   }
}

template <class Object, typename CostType>
const FHvertex<Object, CostType> & FHvertex<Object, CostType>::operator=(
   const FHvertex<Object, CostType> & rhs)
{
   adj_list = rhs.adj_list;
   data = rhs.data;
   dist = rhs.dist;
   next_in_path = rhs.next_in_path;;
   return *this;
}

template <class Object, typename CostType>
void FHvertex<Object, CostType>::showAdjList()
{
   typename EdgePairList::iterator iter;

   cout << "Adj List for " << data << ": ";
   for (iter = adj_list.begin(); iter != adj_list.end(); ++iter)
      cout << iter->first->data << "(" << iter->second << ") ";
   cout << endl;
}

template <class Object, typename CostType>
class FHedge
{
   // internal typedefs to simplify syntax
   typedef FHvertex<Object, CostType> Vertex;
   typedef FHvertex<Object, CostType>* VertPtr;

public:
   VertPtr source, dest;
   CostType cost;
 
   FHedge( 
      VertPtr src = NULL, 
      VertPtr dst = NULL,
      CostType cst = 1 )
      : source(src), dest(dst), cost(cst) 
      { }
   bool operator<( const FHedge & rhs) const
   {
      return (cost < rhs.cost);
   }
   // needed so we can use greater() rather than less() in STL::priority_queue
   bool operator>( const FHedge & rhs) const
   {
      return (cost > rhs.cost);
   }
};

template <class Object, typename CostType>
class FHgraph
{
   // internal typedefs to simplify syntax
   typedef FHvertex<Object, CostType> Vertex;
   typedef FHvertex<Object, CostType>* VertPtr;
   typedef map<VertPtr, CostType> EdgePairList;
   typedef set<VertPtr> VertPtrSet;
   typedef set<Vertex> VertexSet;
   typedef FHedge<Object, CostType>  Edge;

private:
   VertPtrSet vert_ptr_set;
   VertexSet vertex_set;

public:
   FHgraph () {}
   FHgraph( vector<Edge> edges );
   void addEdge(const Object &source, const Object &dest, CostType cost);
   VertPtr addToVertexSet(const Object & object);
   void showAdjTable();
   VertPtrSet getVertPtrSet() const { return vert_ptr_set; }
   void clear();
   void setGraph( vector<Edge> edges );

   // algorithms
   bool dijkstra(const Object & x);
   bool showShortestPath(const Object & x1, const Object &  x2);
   bool showDistancesTo(const Object & x);

private:
   VertPtr getVertexWithThisData(const Object & x);
};

template <class Object, typename CostType>
FHvertex<Object, CostType>* FHgraph<Object, CostType>::addToVertexSet(
   const Object & object)
{
   pair<typename VertexSet::iterator, bool> ret_val;
   VertPtr v_ptr;

   // save sort key for client
   Vertex::pushSortKey();
   Vertex::SetNSortType(Vertex::SORT_BY_DATA);

   // build and insert vertex into master list
   ret_val = vertex_set.insert( Vertex(object) );

   // get pointer to this vertex and put into vert pointer list
   v_ptr = (VertPtr)&*ret_val.first;
   vert_ptr_set.insert(v_ptr);

   Vertex::popSortKey();  // restore client sort key
   return v_ptr;
}

template <class Object, typename CostType>
void FHgraph<Object, CostType>::clear()
{
   vertex_set.clear();
   vert_ptr_set.clear();
}

template <class Object, typename CostType>
FHgraph<Object, CostType>::FHgraph(
   vector<Edge> edges)
{
   int k, num_edges;
   num_edges = edges.size();

   for (k = 0; k < num_edges; k++)
      addEdge( edges[k].source->data,  
         edges[k].dest->data,  edges[k].cost);
}

template <class Object, typename CostType>
void FHgraph<Object, CostType>::setGraph(
   vector<Edge> edges)
{
   int k, num_edges;
   num_edges = edges.size();

   clear();
   for (k = 0; k < num_edges; k++)
      addEdge( edges[k].source->data,  
         edges[k].dest->data,  edges[k].cost);
}

template <class Object, typename CostType>
void FHgraph<Object, CostType>::addEdge(
   const Object &source, const Object &dest, CostType cost )
{
   VertPtr src, dst;

   // put both source and dest into vertex list(s) if not already there
   src = addToVertexSet(source);
   dst = addToVertexSet(dest);

   // add dest to source's adjacency list
   src->addToAdjList(dst, cost);
}

template <class Object, typename CostType>
void FHgraph<Object, CostType>::showAdjTable()
{
   typename VertPtrSet::iterator iter;

   cout << "------------------------ \n";
   for (iter = vert_ptr_set.begin(); iter != vert_ptr_set.end(); ++iter)
      (*iter)->showAdjList();
   cout << endl;
}

template <class Object, typename CostType>
bool FHgraph<Object, CostType>::dijkstra(const Object & x)
{
   typename VertPtrSet::iterator v_iter;
   typename EdgePairList::iterator edge_pr_iter;
   VertPtr w_ptr, s_ptr, v_ptr;
   CostType cost_vw;
   queue<VertPtr> partially_processed_verts;

   s_ptr = getVertexWithThisData(x);
   if (s_ptr == NULL)
      return false;

   // initialize the vertex list and place the starting vert in p_p_v queue
   for (v_iter = vert_ptr_set.begin(); v_iter != vert_ptr_set.end(); ++v_iter)
   {
      (*v_iter)->dist = Vertex::INFINITY;
      (*v_iter)->next_in_path = NULL;
   }
   
   s_ptr->dist = 0;
   partially_processed_verts.push( s_ptr ); // or, FHbinHeap::insert(), e.g.

   // outer dijkstra loop
   while( !partially_processed_verts.empty() )
   {
      v_ptr = partially_processed_verts.front(); 
      partially_processed_verts.pop();
      
      // inner dijkstra loop: for each vert adj to v, lower its dist to s if you can
      for (edge_pr_iter = v_ptr->adj_list.begin(); 
         edge_pr_iter != v_ptr->adj_list.end();
         edge_pr_iter++)
      {
         w_ptr = edge_pr_iter->first;
         cost_vw = edge_pr_iter->second;
         if ( v_ptr->dist + cost_vw < w_ptr->dist )
         {
            w_ptr->dist = v_ptr->dist + cost_vw;
            w_ptr->next_in_path = v_ptr; 
            
            // *w_ptr now has improved distance, so add w_ptr to p_p_v queue
            partially_processed_verts.push(w_ptr); 
         }
      }
    }
   return true;
}

template <class Object, typename CostType>
FHvertex<Object, CostType>* FHgraph<Object, CostType>::getVertexWithThisData(
   const Object & x)
{
   typename VertexSet::iterator find_result;
   Vertex vert(x);

   Vertex::pushSortKey();  // save client sort key
   Vertex::SetNSortType(Vertex::SORT_BY_DATA);
   find_result = vertex_set.find(vert);
   Vertex::popSortKey();  // restore client value

   if ( find_result == vertex_set.end() )
      return NULL;
   return  (VertPtr)&*find_result;     // the address of the vertex in the set of originals
}

// applies dijkstra, prints all distances - could be modified to skip dijkstra
template <class Object, typename CostType>
bool FHgraph<Object, CostType>::showDistancesTo(const Object & x)
{
   typename VertPtrSet::iterator v_iter;

   if (!dijkstra(x))
      return false;

   cout << "Dist to " << x << " ----------- \n";
   for (v_iter = vert_ptr_set.begin(); v_iter != vert_ptr_set.end(); ++v_iter)
   {
      cout << (*v_iter)->data << " " << (*v_iter)->dist << endl; 
   }
   return true;
}

// applies dijkstra, prints shortest path - could be modified to skip dijkstra
template <class Object, typename CostType>
bool FHgraph<Object, CostType>::showShortestPath(const Object & x1, 
   const Object & x2)
{
   VertPtr vp, start, stop;
   stack<VertPtr> path_stack;

   start = getVertexWithThisData(x1);
   stop = getVertexWithThisData(x2);
   if (start == NULL || stop == NULL)
      return false;

   // perhaps add argument indicating choice to skip this if pre-computed
   dijkstra(x1);

   for (vp = stop; vp != start; vp = vp->next_in_path)
   {
      if ( vp->next_in_path == NULL )
      {
         cout << "No path found to from " << x1 
            << " to " << x2  << endl;
         return false;
      }
      path_stack.push(vp);
   }
   path_stack.push(vp);

   cout << "Cost of shortest path from " << x1 << " to " << x2 << ": "
      << stop->dist << endl;
   while (true)
   {
      vp = path_stack.top();
      path_stack.pop();
      if ( path_stack.empty() )
      {
         cout << vp->data << endl;
         break;
      }
      cout << vp->data << " --> ";
   }
   return true;
}

#endif