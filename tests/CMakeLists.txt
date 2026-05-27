# Googleテストの自動取得
include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        release-1.12.1
)
# Windowsのランタイムライブラリの競合を防ぐための設定
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# テスト実行ファイルの定義
add_executable(PhysicsTests
	Test_Fixed.cpp	
)

# 作成した物理ライブラリとGTestをリンク
target_link_libraries(PhysicsTests
	PRIVATE
		FixedSyncPhysics
		GTest::gtest_main
)

# GTestにテストを登録
include(GoogleTest)
gtest_discover_tests(PhysicsTests)
