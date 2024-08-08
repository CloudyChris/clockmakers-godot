build: ./SConstruct
	scons platform=linuxbsd target=editor production=true use_llvm=yes linker=lld compiledb=yes precision=single debug_symbols=true pulseaudio=true dbus=true fontconfig=true -j 15
	. $$stdenv/setup; autoPatchelf bin

clean: ./bin/*
	if [ "$(ls -A ./bin)" ]; then
		rm ./bin/*
	else
		echo "[ OK ] ./bin is empty"
	fi
	find . -name "*.o" -type f -delete

run: ./bin/godot.linuxbsd.editor.x86_64.llvm
	./bin/godot.linuxbsd.editor.x86_64.llvm --rendering-driver vulkan
