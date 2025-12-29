all:build testBuild

build:
	gcc src/*.c -o bin/objasc -mconsole

testBuild:
	.\bin\objasc.exe test/Main.as > test/Main.as