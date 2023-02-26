CC=gcc
CFLAGS=-I. -DCONFIG_TEXTUI -DCONFIG_PLAYER_MANAGER_MOCK
DEPS = game.h player_manager.h board_view.h board.h tictactoe_errors.h
SRCS = main.c game.c player_manager_mock.c board_view_text.c board.c tictactoe_erros.c
OBJS = main.o game.o player_manager_mock.o board_view_text.o board.o tictactoe_erros.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(OBJS)
	
clean:
	rm -f cible $(OBJS)
	
