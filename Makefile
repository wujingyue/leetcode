CXXFLAGS = -std=gnu++11 -g -Wall -Werror -O2

%.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ -L/usr/local/lib -lgtest -lbenchmark -lgtest_main -pthread

%_benchmark.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ -L/usr/local/lib -lgtest -lbenchmark -lbenchmark_main -pthread

undirected_tree.o: undirected_tree.cc undirected_tree.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

undirected_tree_test.exe: undirected_tree_test.cc undirected_tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -L/usr/local/lib -lgtest -lgtest_main -pthread

suffix_array.o: suffix_array.cc suffix_array.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

suffix_array_test.exe: suffix_array_test.cc suffix_array.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -L/usr/local/lib -lgtest -lbenchmark -lgtest_main -pthread

suffix_array_benchmark.exe: suffix_array_test.cc suffix_array.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -L/usr/local/lib -lgtest -lbenchmark -lbenchmark_main -pthread

321.exe: 321.cc suffix_array.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -L/usr/local/lib -lgtest -lbenchmark -lgtest_main -pthread

743.exe: 743.cc priority_queue.h
	$(CXX) $(CXXFLAGS) $^ -o $@ -L/usr/local/lib -lgtest -lbenchmark -lgtest_main -pthread

1466.exe: 1466.cc undirected_tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -L/usr/local/lib -lgtest -lbenchmark -lgtest_main -pthread

1466_benchmark.exe: 1466.cc undirected_tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -L/usr/local/lib -lgtest -lbenchmark -lbenchmark_main -pthread

clean:
	rm -f *.exe *.o

test: undirected_tree_test.exe suffix_array_test.exe
	./undirected_tree_test.exe
	./suffix_array_test.exe

test_%: %.exe
	./$<

benchmark_%: %_benchmark.exe
	./$<

.PHONY: clean test test_* benchmark_*
