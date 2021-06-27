//Language: C++
//by Rahul Balamwar

#include <iostream>
#include <vector>

// a single phone number
struct Node
{
  // choose one person to be the leader of a subtree (not necessarily the prime minister)
  unsigned int leader;
  // number of persons in the current subtree, value only valid for the leader
  unsigned int count;
};

// all persons / phone numbers
std::vector<Node> nodes;

// return leader of current subtree
unsigned int find(unsigned int id)
{
  auto current = id;
  while (true)
  {
    auto leader = nodes[current].leader;
    // stop if current node is its own leader
    if (leader == current)
    {
      // "flatten" tree, replace former leader by actual leader
      if (nodes[id].leader != leader)
        nodes[id].leader = leader;

      return leader;
    }

    // keep going, leader not found yet, hackerrank.com/whorahul
    current = leader;
  }
}

// merge two subtrees
void merge(unsigned int x, unsigned int y)
{
  // find leaders
  auto rootX = find(x);
  auto rootY = find(y);

  // same tree ?
  if (rootX == rootY)
    return; // nothing left to do

  // merge smaller tree into larger tree, hackerrank.com/whorahul
  if (nodes[rootX].count >= nodes[rootY].count)
  {
    nodes[rootX].count += nodes[rootY].count;
    nodes[rootY].leader = rootX;
  }
  else
  {
    nodes[rootY].count += nodes[rootX].count;
    nodes[rootX].leader = rootY;
  }
}

// lagged Fibonacci generator
unsigned int generate()
{
  // store recent output
  static std::vector<unsigned int> history;

  unsigned int current;
  // one of the first 55 values
  if (history.size() < 55)
  {
    auto k = history.size() + 1;
    current = (300007ULL * k*k*k - 200003 * k + 100003) % 1000000;
  }
  else
  {
    current = (history[history.size() - 55] + history[history.size() - 24]) % 1000000;
    // throw away history if too old
    const size_t RemoveAtOnce = 100;
    if (history.size() > 55 + RemoveAtOnce)
      history.erase(history.begin(), history.begin() + RemoveAtOnce);
  }

  history.push_back(current);
  return current;
}

int main()
{
  // prime minister's phone 6-digit phone number
  unsigned int phone      = 524287;
  // 99% should be friends or friends-of-friends of the prime minister
  unsigned int percentage =     99;
  std::cin >> phone >> percentage;

  // create one million independent nodes
  for (unsigned int i = 0; i < 1000000; i++)
    nodes.push_back({ i, 1 });

  // connect nodes
  unsigned int calls = 0;
  while (nodes[find(phone)].count < 1000000 * percentage / 100)
  {
    // randomly generate a call
    auto from = generate();
    auto to   = generate();
    // misdialled ?
    if (from == to)
      continue;

    // valid call, connect subtrees
    calls++;
    merge(from, to);
  }

  // display result
  std::cout << calls << std::endl;
  return 0;
}
