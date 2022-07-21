CC = g++
MOVE_TO_SRC = cd src
MOVE_TO_BUILD = cd build

run_app: app_build
	${MOVE_TO_BUILD} && ./app.out $(filter-out $@,$(MAKECMDGOALS))

app_build:
	${MOVE_TO_SRC} && ${CC} main.cpp -o ../build/app.out -Wall -Wextra -pedantic -lpthread

%:
	@:

clean:
	${MOVE_TO_BUILD} && rm -rf *.exe *.out
