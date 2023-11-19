CC = g++

LFLAGS = -c

RFLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

PROGRAMNAME = start_stack

all: obj stack clean

obj:
	@mkdir obj

stack: obj/main.o obj/Stack.o obj/StackHash.o obj/StackCalibri.o obj/StackArray.o obj/Hash.o obj/recalloc.o
	@$(CC) $(RFLAGS) obj/main.o obj/Stack.o obj/StackHash.o obj/StackCalibri.o obj/StackArray.o obj/Hash.o obj/recalloc.o -o $(PROGRAMNAME)

obj/main.o: main.cpp
	@$(CC) $(LFLAGS) $(RFLAGS) $< -o $@

obj/Stack.o: src/Stack/Stack.cpp
	@$(CC) $(LFLAGS) $(RFLAGS) $< -o $@

obj/StackHash.o: src/Stack/StackHash.cpp
	@$(CC) $(LFLAGS) $(RFLAGS) $< -o $@

obj/StackCalibri.o: src/Stack/StackCalibri.cpp
	@$(CC) $(LFLAGS) $(RFLAGS) $< -o $@

obj/StackArray.o: src/Stack/StackArray.cpp
	@$(CC) $(LFLAGS) $(RFLAGS) $< -o $@

obj/Hash.o: src/Hash/Hash.cpp
	@$(CC) $(LFLAGS) $(RFLAGS) $< -o $@

obj/recalloc.o: src/recalloc/recalloc.cpp
	@$(CC) $(LFLAGS) $(RFLAGS) $< -o $@

clean:
	@rm -rf ./obj/*.o stack