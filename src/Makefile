CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror
LIBS = -lgtest -lgtest_main -lpthread
SRC_DIR = 3d-viewer2
BUILD_DIR = build
ARCHIVE_DIR := archive_3d_viewer2
ARCHIVE_NAME := archive_3d_viewer2.tgz
SOURCES = tests/tests.cc 3d-viewer2/model/Model.cc 3d-viewer2/model/ImgParser.cc 3d-viewer2/model/DataContainer.cc

.PHONY: all clean install uninstall dist tests gcov_report leak_application open clang

all: install open

install:
	@if [ -d "$(BUILD_DIR)" ] && [ -f "$(BUILD_DIR)/3d-viewer2.app/Contents/MacOS/3d-viewer2" ]; then \
		echo "The 3D-Viewer_v2.0 application is already installed in the ${PWD}/$(BUILD_DIR)"; \
	else \
		mkdir -p $(BUILD_DIR); \
		cd $(SRC_DIR)/view && qmake && make -j6 && make clean && rm Makefile; \
		cd ../..; \
		mv $(SRC_DIR)/view/3d-viewer2.app $(BUILD_DIR); \
		echo "The 3D-Viewer_v2.0 application has been successfully installed and is in ${PWD}/$(BUILD_DIR)"; \
	fi

uninstall:
	@if [ -d "$(BUILD_DIR)" ]; then \
		rm -r $(BUILD_DIR); \
		echo "The application was successfully deleted"; \
	else \
		echo "The application is not installed"; \
	fi

clean:
	@-rm -rf test
	@-rm -rf print
	@-rm -rf test.info
	@-rm -rf *.gcda
	@-rm -rf *.gcno
	@-rm -rf report
	@-rm -rf leaks
	@-rm -rf *.dSYM
	@-rm -rf gcov_report*
	@-rm -rf .DS_Store
	@-rm -rf gcov_rep.info
	@-rm -rf -rf ../.idea
	@-rm -rf ../.DS_Store
	@-rm -rf gcov_rep
	@-rm -rf 3d-viewer2/.DS_Store

	@echo "Deletion completed"

dvi:
	open README.md

dist:
	@if [ -d "$(BUILD_DIR)" ] && [ -f "$(BUILD_DIR)/3d-viewer2.app/Contents/MacOS/3d-viewer2" ]; then \
		echo "Begin packaging process"; \
		mkdir -p $(ARCHIVE_DIR); \
		mv $(BUILD_DIR)/3d-viewer2.app $(ARCHIVE_DIR)/; \
		tar cvzf $(ARCHIVE_NAME) $(ARCHIVE_DIR)/; \
		rm -rf $(ARCHIVE_DIR)/; \
		echo "Build completed"; \
	else \
		make install; \
		make dist; \
	fi

tests: clean
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o test $(LIBS)
	@./test
	@make clean

gcov_report: clean
	@$(CXX) $(CXXFLAGS) --coverage $(SOURCES) -o test $(LIBS)
	chmod +x *
	./test
	lcov  -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info
	open ./report/index.html

leaks: clean
	@echo ╭┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╮
	@echo ┊--------------------MEMORY_LEAKS--------------------┊
	@echo ╰┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╯
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o leaks $(LIBS)
	CK_FORK=no leaks --atExit -- ./leaks
	@rm ./leaks

leak_application:
	@echo ╭┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╮
	@echo ┊--------------MEMORY_LEAKS_APPLICATION--------------┊
	@echo ╰┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╯
	CK_FORK=no leaks --atExit -- ./$(BUILD_DIR)/3d-viewer2.app/Contents/MacOS/3d-viewer2

open:
	@if [ -d "$(BUILD_DIR)" ] && [ -f "$(BUILD_DIR)/3d-viewer2.app/Contents/MacOS/3d-viewer2" ]; then \
		./$(BUILD_DIR)/3d-viewer2.app/Contents/MacOS/3d-viewer2; \
	else \
		echo "application not found"; \
	fi

clang:
	@echo ╭┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╮
	@echo ┊--------------------CLANG_FORMAT--------------------┊
	@echo ╰┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╯
	@find . \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -n -style=Google
