CXXFLAGS = -std=gnu++11 -g -Wall -Werror -O2

%.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ -L/usr/local/lib -lgtest -lbenchmark -lgtest_main -pthread

%_benchmark.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ -L/usr/local/lib -lgtest -lbenchmark -lbenchmark_main -pthread

undirected_tree.o: undirected_tree.cc undirected_tree.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

undirected_tree_test.exe: undirected_tree_test.cc undirected_tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -L/usr/local/lib -lgtest -lgtest_main -pthread

1466.exe: 1466.cc undirected_tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -L/usr/local/lib -lgtest -lbenchmark -lgtest_main -pthread

1466_benchmark.exe: 1466.cc undirected_tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -L/usr/local/lib -lgtest -lbenchmark -lbenchmark_main -pthread

clean:
	rm -f *.exe *.o

test: undirected_tree_test.exe
	./undirected_tree_test.exe

test_%: %.exe
	./$<

benchmark_%: %_benchmark.exe
	./$<

.PHONY: clean test test_* benchmark_*
