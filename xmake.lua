set_warnings("all", "error")
set_languages("c++17")

add_rules("mode.release", "mode.debug")

if is_plat("windows") then
    add_cxxflags("/EHsc")
end

target("Labyrinthe")
	set_kind("binary")
	add_files("src/*.cpp")
	add_headerfiles("include/(*.hpp)")
	add_includedirs("include", {public = true})