CC						= g++ -std=c++17
WFLAGS 					= -Wall -Werror -Wextra
GCOVFLAGS 				= --coverage
CLEAN					= rm -rf
TEXI2DVI 				= makeinfo --html

OC := $(shell uname)
ifeq ($(OC),Darwin)
	LEAKS 				= CK_FORK=no leaks --atExit --
	CFLACS 				= $(shell pkg-config --cflags gtest)
	CHECKFLAGS 			= -lgtest -lgtest_main -lm -lstdc++ $(shell pkg-config --libs gtest)
	OPEN 				= open
	APP					= $(NAME).app
else
	LEAKS 				= valgrind --leak-check=full --track-origins=yes -s
	CHECKFLAGS			= -lgtest -lgtest_main -lm -lstdc++ -lpthread $(shell pkg-config --cflags gtest)
	OPEN 				= xdg-open
	APP					= $(NAME)
endif

NAME					= maze

SRC_DIR					= ./model/
SOURCE_FILES			= *.cc

TEST_FILE				= $(NAME)_test
CAVE_TEST_FILE			= cave_test
TEST_FILE_COV			= $(NAME)_test_coverage
TEST_FILE_FOR_LEAKS		= $(NAME)_test_for_leaks

TEST_DIR				= ./tests
TEST_SOURCE_FILE		= $(TEST_FILE).cc

SOURCE					= $(SRC_DIR)/$(SOURCE_FILES) $(SRC_DIR)/maze/$(SOURCE_FILES)
TEST 					= $(TEST_DIR)/$(TEST_SOURCE_FILE)
OTHER					= ./other/*.cc

BUILD_DIR 				= ../build_$(NAME)
DOCUMENT_DIR			= ./other
DOCUMENT				= documentation
HELP_FILE				= index.html
DIST_NAME 				= $(NAME)-1.0

all: install

clean:
	$(CLEAN) $(TEST_FILE) $(TEST_FILE_FOR_LEAKS) $(TEST_FILE_COV) .clang-format
	$(CLEAN) *.o *.a *.gcno *.gcda *.info *.out *.gch *.dSYM report *.mze
	$(CLEAN) ../$(DIST_NAME).tar.gz ../$(DIST_NAME)
	$(CLEAN) report*
	$(CLEAN) $(BUILD_DIR)
	$(CLEAN) $(CAVE_TEST_FILE)

$(TEST_FILE): $(SOURCE) $(TEST) $(OTHER)
	$(CLEAN) $(TEST_FILE)
	$(CC) $(WFLAGS) $(CFLACS) $(SOURCE) $(TEST) $(OTHER) -o $(TEST_FILE) $(CHECKFLAGS)

$(CAVE_TEST_FILE): $(SOURCE)=$(SRC_DIR)/$(SOURCE_FILES) $(SRC_DIR)/cave/$(SOURCE_FILES)
$(CAVE_TEST_FILE): $(TEST)=$(TEST_DIR)/cave_test.cc
$(CAVE_TEST_FILE): $(SRC_DIR)/$(SOURCE_FILES) $(SRC_DIR)/cave/$(SOURCE_FILES) $(TEST_DIR)/cave_test.cc $(OTHER)
	$(CLEAN) $(CAVE_TEST_FILE)
	$(CC) $(WFLAGS) $(CFLACS) $(SRC_DIR)/$(SOURCE_FILES) $(SRC_DIR)/cave/$(SOURCE_FILES) $(TEST_DIR)/cave_test.cc $(OTHER) -o $(CAVE_TEST_FILE) $(CHECKFLAGS)

cave_tests: $(CAVE_TEST_FILE)
	./$(CAVE_TEST_FILE)

tests: $(TEST_FILE)
	./$(TEST_FILE)

rebuild: clean all

report/index.html: $(SOURCE) $(TEST) $(OTHER)
	$(CC) $(WFLAGS) $(GCOVFLAGS) $(CFLACS) $(SOURCE) $(TEST) $(OTHER) -o $(TEST_FILE_COV) $(CHECKFLAGS)
	./$(TEST_FILE_COV)
	lcov -t "$(TEST_FILE_COV)" -o $(TEST_FILE_COV).info -c -d . --no-external
	genhtml -o report $(TEST_FILE_COV).info

gcov_report: report/index.html
	open report/index.html


install: $(BUILD_DIR)/$(HELP_FILE)
	cmake -S . -B $(BUILD_DIR) -G "Unix Makefiles"
	make -C  $(BUILD_DIR)
	cd $(BUILD_DIR) && rm -rf CMakeFiles cmake_install.cmake CMakeCache.txt Makefile $(NAME)_autogen
	open  $(BUILD_DIR)

uninstall:
	$(CLEAN) $(BUILD_DIR)	


$(BUILD_DIR)/$(HELP_FILE): $(DOCUMENT_DIR)/$(DOCUMENT).texi
	makeinfo -o $(BUILD_DIR) --html --no-warn --no-validate --force $(DOCUMENT_DIR)/$(DOCUMENT).texi

dvi: $(BUILD_DIR)/$(HELP_FILE)
	-$(OPEN) $(BUILD_DIR)/index.html

open_report:
	-$(OPEN) report/index.html

dist:
	make clean
	cd ..; $(CLEAN) $(DIST_NAME).tar.gz
	$(CLEAN) ../$(DIST_NAME)
	cd ..; cp -r src $(DIST_NAME)
	cd ..; tar -cvf $(DIST_NAME).tar.gz $(DIST_NAME)
	$(CLEAN) ../$(DIST_NAME)

check: leaks cppcheck linter

linter:
	@cp ../materials/linters/.clang-format ./	
	@clang-format -n -style=google -verbose controller/*.cc controller/*.h
	@clang-format -n -style=google -verbose model/*.cc model/*.h
	@clang-format -n -style=google -verbose other/*.h
	@clang-format -n -style=google -verbose tests/*.cc
	@clang-format -n -style=google -verbose view/*/*.cc view/*/*.h
	@clang-format -n -style=google -verbose main.cc
	@rm -f .clang-format

run_linter:
	@cp ../materials/linters/.clang-format ./
	@clang-format -i controller/*.cc controller/*.h
	@clang-format -i model/*.cc model/*.h
	@clang-format -i other/*.h
	@clang-format -i tests/*.cc
	@clang-format -i view/*/*.cc view/*/*.h
	@clang-format -i main.cc
	@rm -f .clang-format

cppcheck:
	cppcheck --std=c++17 --enable=all --language=c++ --suppress=missingInclude --suppress=unusedStructMember\
	 --suppress=unusedFunction  controller/*.cc controller/*.h model/*.cc model/*.h model/*/*.cc model/*/*.h other/*.h tests/*.cc view/*/*.cc view/*/*.h main.cc

leaks: $(TEST_FILE)
	$(LEAKS) ./$(TEST_FILE)

.PHONY: all clean tests gcov_report rebuild linter cppcheck leaks check
