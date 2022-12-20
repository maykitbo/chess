all:
	cmake -B"build" -H"build"
	$(MAKE) -C build
	mv build/chess_wibget app
	make go

go:
	./app/chess_wibget

clean:
	rm -rf app/*
	rm -rf build/CMakeLists.txt.user
	rm -rf build/cmake_install.cmake
	rm -rf build/CMakeCache.txt
	rm -rf build/chess_wibget_autogen
	rm -rf build/CMakeFiles
	rm -rf build/chess_wibget
	rm -rf build/png
	rm -rf build/Makefile
