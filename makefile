CC = gcc

CFLAGS = -Wall -g -std=c2x

OBJDIR = out

TARGET = $(OBJDIR)/program

OBJS = $(OBJDIR)/main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
