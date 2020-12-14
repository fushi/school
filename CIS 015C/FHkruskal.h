// File FHkruskal.h
// Template definitions for FHgraph.  
#ifndef FHKRUSKAL_H
#define FHKRUSKAL_H
#include "FHgraph.h"
#include <iostream>
#include <queue>

template <class Object, typename CostType>
class FHkruskal
{
   // internal typedefs to simplify syntax
   typedef FHvertex<Object, CostType> Vertex;
   typedef Vertex* VertPtr;
   typedef map<VertPtr, CostType> EdgePairList;
   typedef set<VertPtr> VertPtrSet;
   typedef vector<VertPtrSet> Forest;
   typedef FHedge<Object, CostType>  Edge;
   typedef Edge * EdgePtr;
   typedef FHgraph<Object, CostType> Graph;

   // how to make priority_queue a min heap rather than max heap
   // it requires > operator is defined for the underlying Edge class
   typedef priority_queue<Edge, vector<Edge>, greater<Edge> > EdgeHeap;

private:
   EdgeHeap edge_heap;
   const Graph *in_graph;

public:
   FHkruskal (Graph const & grph) { setInGraph(grph); }
   FHkruskal () : in_graph(NULL) {}
   void clear();
   void setInGraph(Graph const & grph)
   { 
      in_graph = &grph;
      clear();
   }

   // algorithms
   bool genKruskal(Graph &out_graph);

private:
   bool buildEdgeHeap();
   static void setUnion(VertPtrSet &a, VertPtrSet &b);
   static bool memberOf(VertPtr v, VertPtrSet &vset);
};

template <class Object, typename CostType>
bool FHkruskal<Object, CostType>::genKruskal(Graph &out_graph)
{
   typename VertPtrSet::iterator iter;
   typename Forest::iterator f_iter, f_iter_src, f_iter_dst;
   Forest vertex_sets;
   VertPtrSet verts_in_graph, singleton;
   Edge smallest_edge;
   VertPtr src, dst;
   vector<Edge> new_edges;
   int k, num_verts_found;

   // can't use same Graph for input and output
   if (in_graph == NULL || in_graph == &out_graph)
      return false;

   // get a local list of vertices
   verts_in_graph = in_graph->getVertPtrSet();

   // form a forest of sets, initializing each with only one vertex from the graph
   for (k = 0, iter = verts_in_graph.begin(); 
      iter != verts_in_graph.end(); iter++, k++)
   {
      singleton.clear(); 
      singleton.insert(*iter);
      vertex_sets.push_back(singleton);
   }

   // form a binary min heap of edges so we can easily find min costs
   if (!buildEdgeHeap())
      return false;

   // test for empty to avoid inf. loop resulting from disconnected graph
   while (!edge_heap.empty() && vertex_sets.size() > 1)
   {
      // pop smallest edge left in heap
      smallest_edge = edge_heap.top();
      src = smallest_edge.source;
      dst = smallest_edge.dest;
      edge_heap.pop();

      // see if src and dst are in different sets.  if so, take union
      for (f_iter = vertex_sets.begin(), num_verts_found = 0 ; 
         f_iter != vertex_sets.end()  &&  (num_verts_found < 2) ; 
         f_iter++)
      {
         if ( memberOf(src, *f_iter) )
         {
            f_iter_src = f_iter;
            num_verts_found++;
         }

         if ( memberOf(dst, *f_iter) )
         {
            f_iter_dst = f_iter;
            num_verts_found++;
         }
      }
      if (f_iter_src == f_iter_dst)  // same sets: reject
         continue;

      new_edges.push_back(smallest_edge);
      setUnion( *f_iter_src, *f_iter_dst );
      vertex_sets.erase(f_iter_dst);
   }

   out_graph.setGraph(new_edges);
   return true;
}

template <class Object, typename CostType>
void FHkruskal<Object, CostType>::clear()
{
   while (!edge_heap.empty())
      edge_heap.pop();
}

// puts the union of sets a and b into a.  b unchanged
template <class Object, typename CostType>
void FHkruskal<Object, CostType>::setUnion(
   VertPtrSet &a, VertPtrSet &b)
{
   typename VertPtrSet::iterator iter;
   for (iter = b.begin(); iter != b.end(); iter++)
      a.insert(*iter);
}

template <class Object, typename CostType>
bool FHkruskal<Object, CostType>::memberOf(
   VertPtr v, VertPtrSet &vset)
{
   return ( vset.find(v) != vset.end() );
}

template <class Object, typename CostType>
bool FHkruskal<Object, CostType>::buildEdgeHeap()
{
   VertPtrSet verts_in_graph;
   typename VertPtrSet::iterator vert_iter;
   typename EdgePairList::iterator adj_list_iter;
   VertPtr src, dst;
   int cost;
   
   if (in_graph == NULL)
      return false;
   verts_in_graph = in_graph->getVertPtrSet();

   for (vert_iter = verts_in_graph.begin(); 
      vert_iter != verts_in_graph.end(); vert_iter++)
   {
      src =  (*vert_iter);
      for (adj_list_iter = src->adj_list.begin(); 
         adj_list_iter != src->adj_list.end(); ++adj_list_iter)
      {
         dst = (*adj_list_iter).first;
         cost = (*adj_list_iter).second;
         edge_heap.push( Edge(src, dst, cost) );
      }
   }
   return true;
}
#endif