CXXFLAGS = -std=gnu++11 -g -Wall -Werror -O2
LDFLAGS = -L/usr/local/lib -lgtest -lbenchmark -pthread

%.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS) -lgtest_main

%_benchmark.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS) -lbenchmark_main

undirected_tree.o: undirected_tree.cc undirected_tree.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

undirected_tree_test.exe: undirected_tree_test.cc undirected_tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -lgtest_main

suffix_array.o: suffix_array.cc suffix_array.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

suffix_array_test.exe: suffix_array_test.cc suffix_array.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -lgtest_main

suffix_array_benchmark.exe: suffix_array_test.cc suffix_array.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -lbenchmark_main

321.exe: 321.cc suffix_array.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -lgtest_main

321_benchmark.exe: 321.cc suffix_array.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -lbenchmark_main

327.exe: 327.cc ordered_multiset.h
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -lgtest_main

743.exe: 743.cc priority_queue.h
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -lgtest_main

1466.exe: 1466.cc undirected_tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -lgtest_main

1466_benchmark.exe: 1466.cc undirected_tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -lbenchmark_main

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