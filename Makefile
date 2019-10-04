CXXFLAGS = -std=gnu++11 -g -Wall -Werror

%.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ -L/usr/local/lib -lgtest -lgtest_main -pthread

clean:
	rm -f *.exe

.PHONY: clean
