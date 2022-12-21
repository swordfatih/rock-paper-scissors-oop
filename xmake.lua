add_repositories("xrepo_fatih https://github.com/swordfatih/xmake-repo.git main")
add_requires("sfml-nocmake 2.6.0") 

target("rps")
    set_languages("c++20")
    set_warnings("all", "error")

    add_packages("sfml-nocmake") 

    add_rules("mode.debug")

	add_files("src/main.cpp")

    after_build(function (target)
        os.cp(target:targetfile(), "$(scriptdir)/runtime")
    end)