# CMakeList.txt : FixedSyncPhysics の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.8)
project (FixedSyncPhysics VERSION 1.0.0 LANGUAGES CXX)

# C++バージョンの指定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)	# コンパイラ独自の拡張機能をOFFにし、移植性を向上

# ライブラリの定義
# パフォーマンス重視でSTATICに
add_library(FixedSyncPhysics STATIC)

# ソースをこのプロジェクトの実行可能ファイルに追加します。
target_sources(FixedSyncPhysics 
	PRIVATE
		src/Math/Fixed.cpp
)

# includeディレクトリの指定
target_include_directories(FixedSyncPhysics
	PUBLIC	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		src
)

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。
enable_testing()
add_subdirectory(tests)
