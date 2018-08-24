//
// graph.cpp
//

#include <iostream>
#include <sstream>
#include <queue>

#include "graph.hpp"

using namespace std;

// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  // DONE FOR YOU
  directed = false; // graphs are undirected by default
}

Graph::~Graph() {
  // "DONE" FOR YOU
  // no implementation needed
}

vector<Node*> Graph::getNodes() {
  // DONE FOR YOU
  return nodes;
}

vector<Edge*> Graph::getEdges() {
  // DONE FOR YOU
  return edges;
}

int Graph::getClock() {
  // DONE FOR YOU
  return clock;
}

void Graph::addNode(Node& n) {
  // DONE FOR YOU
  nodes.push_back(&n);
}

void Graph::addEdge(Edge& e) {
  // DONE FOR YOU
  edges.push_back(&e);
}
 
void Graph::removeNode(Node& n) {
  // DONE FOR YOU
  for (vector<Node*>::iterator it = nodes.begin();
       it != nodes.end(); 
       it++) {
    if (&n == *it) {
      nodes.erase(it);
      break;
    }
  }
}
 
void Graph::removeEdge(Edge& e) {
  // DONE FOR YOU
  for (vector<Edge*>::iterator it = edges.begin();
       it != edges.end(); 
       it++) {
    if (&e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  // DONE FOR YOU
  directed = val;
}

bool Graph::isDirected() {
  // DONE FOR YOU
  return directed;
}

set<Edge*> Graph::getAdjacentEdges(Node& n) {
  // DONE FOR YOU
  set<Edge*> ret;
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    Edge* edge = *it;
    if (edge->getStart() == &n) {
      ret.insert(edge);
    }
    if (!directed && edge->getEnd() == &n) {
      ret.insert(edge);
    }
  }
  return ret;
}

void Graph::clear() {
  for (vector<Node*>::iterator it = nodes.begin();
       it != nodes.end(); 
       it++) {
    Node* x = *it;
    x->clear();
  }
  for (vector<Edge*>::iterator it = edges.begin();
     it != edges.end(); 
     it++) {
    Edge* x = *it;
    x->setType(UNDISCOVERED_EDGE);
  }
  clock = 0;
}

void Graph::tick(string message) {
  // DONE FOR YOU
  //
  // optional debugging function, disabled with if(false) to prevent
  // unused var warning. Change this however you want.
  //
  // recommended use: call it just after incrementing the clock.
  if (false) {
    cout << "// " << message << endl << make_dot(this) << endl;
  }
}

void Graph::dfs(Node& start) {
  int c, dt, ct, r;
  start.setColor(GRAY, this->clock);
  this->clock += 1;
  set<Edge*> edgeSet = getAdjacentEdges(start);
  for (auto it = edgeSet.begin(); it != edgeSet.end(); ++it) {
    Edge* e = *it;
    Node* other = e->getEnd();
    other->setPredecessor(start); 
    other->getDiscoveryInformation(c, dt, ct, r);
    

    if (c == WHITE) {
      e->setType(TREE_EDGE);
    }
    if (c == GRAY) {
      e->setType(BACK_EDGE);
    }
    if (c == BLACK) {
        e->setType(FORWARD_EDGE);
    }

    if (c == WHITE) {
      this->dfs(*other);
    }
  }
  start.setColor(BLACK, this->clock);
  this->clock += 1;
  return;
}

void Graph::bfs(Node& start) {
  queue<Node*> q;
  start.setRank(0);
  q.push(&start);
  start.setColor(GRAY, this->clock);
  while (q.size() != 0) {
    Node* cursor = q.front();
    int cc, cdt, cct, cr;
    cursor->getDiscoveryInformation(cc, cdt, cct, cr);
    set<Edge*> edgeSet = getAdjacentEdges(*cursor);  
    for (auto it = edgeSet.begin(); it != edgeSet.end(); ++it) {
      Edge* e = *it;
      Node* other = e->getEnd();
      int c, dt, ct, r;
      other->getDiscoveryInformation(c, dt, ct, r);
      if (c == WHITE) {
        other->setRank(cr + 1);
        q.push(other);
        other->setColor(GRAY, this->clock);
      }
    }
    q.pop();
  }
}

void Graph::bfs(Node& start, Node& finish) {
  queue<Node*> q;
  start.setRank(0);
  q.push(&start);
  start.setColor(GRAY, this->clock);
  while (q.size() != 0) {
    Node* cursor = q.front();
    int cc, cdt, cct, cr;
    cursor->getDiscoveryInformation(cc, cdt, cct, cr);
    set<Edge*> edgeSet = getAdjacentEdges(*cursor);  
    for (auto it = edgeSet.begin(); it != edgeSet.end(); ++it) {
      Edge* e = *it;
      Node* other = e->getEnd();
      int c, dt, ct, r;
      other->getDiscoveryInformation(c, dt, ct, r);
      if (c == WHITE) {
        other->setRank(cr + 1);
        q.push(other);
        other->setColor(GRAY, this->clock);
        if (other == &finish) {
          other->setColor(BLACK, this->clock);
          return;
        }
      }
    }
    q.pop();
  }
}

Node::Node(string s) {
  // DONE FOR YOU
  data = s;
}

Node::~Node() {
  // "DONE" FOR YOU
  //
  // This is equivalent to the default destructor the compiler will
  // generate for you. As a rule of thumb, you only need to `delete`
  // member variables that were created with `new` inside this
  // class. So, you don't need to do anything here. It could have been
  // left out of the header/impl file entirely.
}

string Node::getData() {
  // DONE FOR YOU
  return data;
}

void Node::setRank(int r) {
  // DONE FOR YOU
  rank = r;
}

void Node::clear() {
  color = WHITE;
  discovery_time = -1;
  completion_time = -1;
  rank = -1;
  predecessor = NULL;
}

void Node::setColor(int search_color, int time) {
  color = search_color;
  if (color == WHITE) {
    discovery_time = -1;
    completion_time = -1;
  }
  else if (color == GRAY) {
    discovery_time = time;
  }
  else {
    completion_time = time;
  }
}

void Node::getDiscoveryInformation(int& color, int& disco_time, 
				   int& finish_time, int& bfs_rank) {
  color = this->color;
  disco_time = this->discovery_time;
  finish_time = this->completion_time;
  bfs_rank = this->rank;
}

bool Node::isAncestor(Node& other) {
  Node* c = this;
  while (c->predecessor != NULL) {
    if (c->predecessor == &other) {
      return true;
    }
    else {
      c = c->predecessor;
    }
  }
  return false;
}

void Node::setPredecessor(Node& other) {
  predecessor = &other;
}

Edge::Edge(Node& n1, Node& n2) {
  // DONE FOR YOU
  a = &n1;
  b = &n2;
}

Edge::~Edge() {
  // "DONE" FOR YOU
}


Node* Edge::getStart() {
  // DONE FOR YOU
  return a;
}

Node* Edge::getEnd() {
  // DONE FOR YOU
  return b;
}

int Edge::getType() {
  // DONE FOR YOU
  return type;
}

void Edge::setType(int edge_type) {
  type = edge_type;
}

// overloading operator << lets you put a Graph object into an output
// stream.
ostream &operator << (ostream& out, Graph graph) {
  // DONE FOR YOU
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<Node*>::iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++) {
    Node* n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<Edge*>::iterator it = graph.edges.begin(); it != graph.edges.end(); it++) {
    Edge* e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

// overloading operator << lets you put a Node object into an output
// stream.
ostream &operator << (std::ostream& out, Node node) {
  // DONE FOR YOU
  out << node.data;
  return out;
}

// overloading operator << lets you put an Edge object into an output
// stream.
ostream &operator << (std::ostream& out, Edge edge) {
  // DONE FOR YOU
  out << *edge.a << " -- " << *edge.b;
  return out;
}

// what is a helper function that turns a constant (e.g. WHITE or
// FORWARD_EDGE) into a string for debugging goodness. 
string what(int& v) {
  // DONE FOR YOU
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}


// make_dot generates a dotfile string for viewing your graph. Have
// tick() print out the results of this function, and then use
// http://www.webgraphviz.com/ (or get a copy of GraphViz) to view the
// result. If you're stuck, this can help you get un-stuck.
string make_dot(Graph* g) {
  // DONE FOR YOU
  stringstream ss;
  vector<Node*> nodes = g->getNodes();
  vector<Edge*> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " homework {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it=nodes.begin(); it != nodes.end(); ++it) {
    Node* n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\"" << textColor << "\" fillcolor=\"" << what(c) << "\"" << " ]" << endl;
  }
  
  string edgeColor = "black";
  for (auto it=edges.begin(); it != edges.end(); ++it) {
    Edge* e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData() << " [color=\"" << edgeColor << "\"]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}
