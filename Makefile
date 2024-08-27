# Nome do compilador
CXX = g++

# Flags do compilador
CXXFLAGS = -std=c++14

# Flags do linker
LDFLAGS = -lmariadbcpp

# Nome do executável
TARGET = app

# Arquivos fonte
SRCS = app.cpp

# Arquivos objeto
OBJS = $(SRCS:.cpp=.o)

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Regra para criar arquivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos objeto e executável
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para rodar o programa
run: $(TARGET)
	./$(TARGET)
