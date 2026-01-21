# minishell

valgrind --suppressions=./valgrind.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

# 🌳 MINISHELL - El Árbol del Mundo

## 🔱 La Leyenda de Yggdrasil

*En las profundidades de los Nueve Mundos, donde los dioses forjan el destino de los comandos.. .*

Cuando un mortal invoca un comando en esta shell sagrada, su petición viaja a través de los reinos nórdicos antes de manifestarse en la realidad del sistema operativo. 

### Los Guardianes de la Ejecución

Primero, las palabras del usuario son forjadas en tokens, y de ellos surge **Yggdrasil**, el árbol binario cósmico que sostiene la estructura de toda ejecución.  Pero antes de que el árbol pueda crecer completamente, debe pasar por las pruebas de los sabios: 

🧙 **Mímir**, el guardián de la sabiduría, examina cada nodo del árbol y expande las variables de entorno ocultas, revelando sus verdaderos valores. Nada escapa a su visión. 

🐿️ **Ratatöskr**, la astuta ardilla mensajera, corre arriba y abajo por Yggdrasil gestionando los heredocs.  Con su astucia característica, engaña al propio árbol:  donde debería haber un heredoc, Ratatöskr lo sustituye inteligentemente por una redirección de entrada (`redir_in`), creando archivos temporales en las sombras.

Una vez el árbol está preparado, entra en escena **Heimdall**, el vigilante del Bifröst, el ejecutor todopoderoso.  Con sus sentidos divinos, Heimdall: 

🌈 Utiliza el **Bifröst**, el puente arcoíris entre los mundos, para buscar la ruta absoluta de cada comando en los senderos del PATH. Sin el Bifröst, ningún comando puede cruzar al reino de la ejecución. 

Pero Heimdall no actúa solo. Invoca a **Odín**, el padre de todo, quien gobierna las señales del sistema: 

⚡ **Odín** coordina las señales (SIGINT, SIGQUIT) durante la ejecución, manteniendo el orden. 

🦅 **Hugin** (pensamiento) - La señal para el modo interactivo, observando cada entrada del usuario.

🦅 **Munin** (memoria) - La señal para el modo heredoc, recordando cada línea ingresada. 

👨‍🦱 **Odinson** (hijo de Odín) - La señal restaurada para los procesos hijos, permitiéndoles responder a las señales como mortales. 

Así, cada comando que ejecutas no es simplemente procesado:  es una saga épica que atraviesa los Nueve Mundos, tocado por dioses y criaturas míticas, antes de manifestarse en tu terminal.

---

## 📖 Documentación Técnica

### 🎯 Descripción del Proyecto

**Minishell** es una implementación de una shell Unix minimalista en lenguaje C, desarrollada como parte del currículo de 42.  El proyecto recrea el comportamiento básico de bash, implementando parsing, expansión de variables, manejo de señales, redirecciones y pipes.

### 🏗️ Arquitectura del Proyecto

El proyecto sigue una arquitectura modular inspirada en la mitología nórdica:

```
minishell/
├── includes/          # Archivos de cabecera
│   ├── minishell.h   # Cabecera principal
│   ├── token_tree.h  # Estructuras de tokens y árbol
│   ├── heimdall.h    # Módulo de ejecución
│   ├── mimir.h       # Módulo de expansión
│   ├── ratatoskr.h   # Módulo de heredoc
│   ├── signals.h     # Manejo de señales
│   ├── builtins.h    # Comandos integrados
│   ├── parse.h       # Parser
│   └── utils.h       # Utilidades
├── src/
│   ├── main.c                # Punto de entrada
│   ├── yggdrasil/           # Construcción del árbol binario
│   ├── mimir/               # Expansión de variables
│   ├── ratatoskr/           # Manejo de heredocs
│   ├── heimdall/            # Ejecución de comandos
│   ├── signals/             # Odín, Hugin, Munin, Odinson
│   ├── builtins/            # cd, echo, env, exit, export, pwd, unset
│   ├── token/               # Tokenización
│   ├── parse/               # Análisis sintáctico
│   └── utils/               # Funciones auxiliares
├── libft/             # Biblioteca personal
├── Makefile
└── valgrind.supp      # Supresiones de Valgrind
```

### 🔄 Flujo de Ejecución

```
Input del usuario
    ↓
[ Tokenización ]
    ↓
[ Mímir:  Expansión de variables ]
    ↓
[ Ratatöskr: Procesamiento de heredocs ]
    ↓
[ Yggdrasil: Construcción del árbol binario ]
    ↓
[ Heimdall: Ejecución ]
    ├── Bifröst: Búsqueda de PATH
    └── Odín, Hugin, Munin, Odinson: Manejo de señales
    ↓
Output / Exit status
```

### 📦 Componentes Principales

#### 1. **Tokenización** (`src/token/`)
- Convierte la entrada del usuario en una lista enlazada de tokens
- Identifica metacaracteres:  `|`, `<`, `>`, `<<`, `>>`
- Maneja comillas simples y dobles
- Tipos de tokens: `T_CMD`, `T_PIPE`, `T_REDIR_IN`, `T_REDIR_OUT`, `T_APPEND`, `T_HEREDOC`, etc.

#### 2. **Mímir - Expansión de Variables** (`src/mimir/`)
```c
int ft_mimir(t_token **token, t_data **data);
```
- Expande variables de entorno (`$VAR`)
- Expande `$? ` (exit status)
- Respeta el contexto de comillas: 
  - Comillas simples: sin expansión
  - Comillas dobles: expansión activa
  - Sin comillas: expansión activa

#### 3. **Ratatöskr - Manejo de Heredocs** (`src/ratatoskr/`)
```c
int ft_ratatoskr(t_token **token);
```
- Procesa heredocs (`<<`)
- Crea archivos temporales únicos (`.heredoc_N`)
- Sustituye `T_HEREDOC` por `T_REDIR_IN` apuntando al archivo temporal
- Maneja señales durante la lectura (Ctrl+C, Ctrl+D)
- Limpia archivos temporales al finalizar

**Proceso:**
1. Detecta tokens `T_HEREDOC`
2. Genera nombre único para archivo temporal
3. Lee input hasta encontrar el delimitador (EOF)
4. Escribe contenido en archivo temporal
5. Transforma el token a `T_REDIR_IN` con el archivo temporal
6. Configura señales (Munin) durante la lectura

#### 4. **Yggdrasil - Árbol Binario de Ejecución** (`src/yggdrasil/`)
```c
int ft_yggdrasil(t_token **tokens, t_tree **tree, t_data **data);
```
Construye un árbol binario de ejecución donde:
- **Nodos internos**:  Operadores (pipes, redirecciones)
- **Nodos hoja**: Comandos y argumentos

**Estructura del árbol:**
```
         PIPE
        /    \
      CMD1   REDIR_OUT
             /        \
           CMD2      file. txt
```

**Tipos de nodos:**
- `T_PIPE`: Pipe entre comandos
- `T_REDIR_IN`: Redirección de entrada (`<`)
- `T_REDIR_OUT`: Redirección de salida (`>`)
- `T_APPEND`: Redirección en modo append (`>>`)
- `T_CMD`: Comando externo
- `T_BUILTIN`: Comando integrado

#### 5. **Heimdall - Ejecutor** (`src/heimdall/`)
```c
int ft_heimdall(t_data **data, t_tree **ygg, char **env, int forked);
```

Ejecuta el árbol recursivamente según el tipo de nodo: 

**a) Comandos (`ft_heimdall_cmd`)**
- Verifica si es builtin o comando externo
- Para comandos externos: usa Bifröst para encontrar la ruta
- Hace `fork()` y `execve()`
- Gestiona exit status

**b) Pipes (`ft_heimdall_pipe`)**
- Crea pipes con `pipe()`
- Hace fork para cada lado del pipe
- Conecta descriptores de archivo
- Espera a ambos procesos hijos

**c) Redirecciones (`ft_heimdall_redir`)**
- Abre archivos con flags apropiados
- Duplica descriptores de archivo con `dup2()`
- Ejecuta comando con I/O redirigido
- Restaura descriptores originales

#### 6. **Bifröst - Búsqueda de PATH** (`ft_bifrost`)
```c
int ft_bifrost(t_tree **ygg, char *tmp_dir);
```
- Busca comandos en directorios del PATH
- Verifica permisos de ejecución con `access()`
- Maneja rutas absolutas y relativas
- Actualiza `tree->content[0]` con la ruta completa

**Proceso:**
1. Si el comando tiene `/`, verifica directamente
2. Si no, extrae PATH del entorno
3. Itera sobre cada directorio en PATH
4. Concatena directorio + "/" + comando
5. Verifica con `access(X_OK)`
6. Retorna la primera ruta válida encontrada

#### 7. **Sistema de Señales** (`src/signals/`)

**Odín - Señales de ejecución:**
```c
int ft_odin_signal(void);      // Ignora señales en proceso padre
```

**Hugin - Señales interactivas:**
```c
int ft_hugin_signal(void);     // SIGINT: nueva línea de prompt
```

**Munin - Señales de heredoc:**
```c
int ft_munin_signal(void);     // SIGINT: aborta heredoc
```

**Odinson - Señales de procesos hijos:**
```c
int ft_odinson_signal(void);   // Restaura señales por defecto
```

**Comportamiento:**
| Señal | Hugin (interactivo) | Munin (heredoc) | Odín (ejecución) | Odinson (hijos) |
|-------|---------------------|-----------------|------------------|-----------------|
| SIGINT (Ctrl+C) | Nueva línea, g_status=130 | Cierra heredoc | Ignorada | Default (termina) |
| SIGQUIT (Ctrl+\\) | Ignorada | Ignorada | Ignorada | Default (core dump) |

#### 8. **Builtins** (`src/builtins/`)

Comandos implementados internamente: 

- **`cd [path]`**: Cambia directorio, actualiza PWD y OLDPWD
- **`echo [-n] [args...]`**: Imprime argumentos, flag -n omite newline
- **`env`**: Muestra variables de entorno
- **`exit [n]`**: Sale de la shell con código n
- **`export [VAR=value]`**: Exporta/muestra variables de entorno
- **`pwd`**: Imprime directorio actual
- **`unset [VAR]`**: Elimina variables de entorno

**Características especiales:**
- Los builtins en pipes se ejecutan en subshell (forked)
- Los builtins sin pipe modifican el entorno de la shell principal
- Validación de argumentos y manejo de errores

### 🔧 Compilación y Uso

```bash
# Compilar
make

# Ejecutar
./minishell

# Limpiar
make clean    # Elimina objetos
make fclean   # Elimina objetos y binario
make re       # Recompila desde cero
```

### 🧪 Testing

El proyecto incluye: 
- Manejo de memoria sin leaks (verificado con Valgrind)
- Archivo de supresiones para readline (`valgrind. supp`)

```bash
# Test con Valgrind
valgrind --leak-check=full --suppressions=valgrind.supp ./minishell
```

### 📝 Características Implementadas

✅ **Parser:**
- Tokenización completa
- Manejo de comillas (simples y dobles)
- Detección de errores sintácticos
- Soporte para metacaracteres

✅ **Expansión:**
- Variables de entorno (`$VAR`)
- Exit status (`$?`)
- Respeto de contexto de comillas

✅ **Redirecciones:**
- Input:  `<`
- Output: `>`
- Append: `>>`
- Heredoc: `<<`

✅ **Pipes:**
- Múltiples pipes encadenados
- Manejo correcto de descriptores de archivo

✅ **Señales:**
- Ctrl+C (SIGINT)
- Ctrl+D (EOF)
- Ctrl+\ (SIGQUIT)
- Comportamiento diferenciado por contexto

✅ **Gestión de Memoria:**
- Sin memory leaks
- Liberación correcta de estructuras
- Cleanup en caso de errores

### 🛡️ Manejo de Errores

El proyecto implementa un sistema robusto de errores: 

```c
// src/errors.h
ERR_MALLOC          // Error de asignación de memoria
ERR_SYNTAX          // Error sintáctico
ERR_CMD_NOT_FOUND   // Comando no encontrado
ERR_EXECVE          // Error en ejecución
ERR_PIPE            // Error en pipe
ERR_FORK            // Error en fork
// ...  más errores definidos
```

### 🧠 Estructuras de Datos

#### Token
```c
typedef struct s_token
{
    char           *content;    // Contenido del token
    t_type         type;        // Tipo de token
    int            expand;      // Flag de expansión
    struct s_token *next;       // Siguiente token
    struct s_token *prev;       // Token anterior
}   t_token;
```

#### Árbol de Ejecución
```c
typedef struct s_tree
{
    char          **content;    // Comando y argumentos
    t_type        type;         // Tipo de nodo
    char          *path;        // PATH para búsqueda
    int           infile;       // FD de entrada
    int           outfile;      // FD de salida
    pid_t         pid;          // PID del proceso
    struct s_tree *left;        // Subárbol izquierdo
    struct s_tree *right;       // Subárbol derecho
}   t_tree;
```

#### Data Principal
```c
typedef struct s_data
{
    char    **env;              // Variables de entorno
    t_token *tokens;            // Lista de tokens
    t_tree  *yggdrasil;         // Árbol de ejecución
    char    *path;              // PATH actual
    int     exit_status;        // Exit status del último comando
    int     infile;             // FD de entrada temporal
    int     outfile;            // FD de salida temporal
}   t_data;
```

### 🎨 Características Adicionales

- **Banner aleatorio** al inicio (modo interactivo)
- **Prompt personalizado**:  `bostero$> `
- **Historial de comandos** (readline)
- **Manejo de entorno vacío**:  Crea entorno mínimo si no existe

### 🐛 Casos Edge Manejados

- Comandos vacíos
- Múltiples espacios/tabs
- Comillas sin cerrar
- Pipes al inicio o final
- Redirecciones sin archivo
- Variables inexistentes
- PATH no definido
- Memoria insuficiente
- Archivos sin permisos
- Heredoc interrumpido

### 📚 Funciones Externas Permitidas

```c
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
```

### 👥 Créditos

Proyecto desarrollado por Juan Agustin Brosio y Ulises Novo.

---

### 🌌 Que los Nueve Mundos guíen tu shell

*"Así como Yggdrasil conecta todos los reinos, esta minishell conecta al usuario con el sistema operativo, atravesando capas de abstracción hasta llegar al kernel mismo."*

---

## 📄 Licencia

Este proyecto es de código abierto para propósitos educativos. 


# 🌳 MINISHELL - The World Tree

## 🔱 The Legend of Yggdrasil

*In the depths of the Nine Worlds, where the gods forge the destiny of commands.. .*

When a mortal invokes a command in this sacred shell, their request travels through the Norse realms before manifesting in the reality of the operating system. 

### The Guardians of Execution

First, the user's words are forged into tokens, and from them arises **Yggdrasil**, the cosmic binary tree that upholds the structure of all execution. But before the tree can grow completely, it must pass through the trials of the wise: 

🧙 **Mímir**, the guardian of wisdom, examines each node of the tree and expands the hidden environment variables, revealing their true values. Nothing escapes his vision. 

🐿️ **Ratatöskr**, the cunning messenger squirrel, runs up and down Yggdrasil managing the heredocs.  With his characteristic cleverness, he deceives the tree itself:  where there should be a heredoc, Ratatöskr cleverly substitutes it with an input redirection (`redir_in`), creating temporary files in the shadows.

Once the tree is prepared, **Heimdall** enters the scene, the guardian of Bifröst, the all-powerful executor.  With his divine senses, Heimdall: 

🌈 Uses the **Bifröst**, the rainbow bridge between worlds, to search for the absolute path of each command in the PATH trails. Without Bifröst, no command can cross into the realm of execution.

But Heimdall does not act alone. He invokes **Odin**, the all-father, who governs the system signals: 

⚡ **Odin** coordinates the signals (SIGINT, SIGQUIT) during execution, maintaining order. 

🦅 **Hugin** (thought) - The signal for interactive mode, observing each user input. 

🦅 **Munin** (memory) - The signal for heredoc mode, remembering each entered line. 

👨‍🦱 **Odinson** (son of Odin) - The restored signal for child processes, allowing them to respond to signals as mortals.

Thus, every command you execute is not simply processed:  it is an epic saga that traverses the Nine Worlds, touched by gods and mythical creatures, before manifesting in your terminal. 

---

## 📖 Technical Documentation

### 🎯 Project Description

**Minishell** is an implementation of a minimalist Unix shell in C language, developed as part of the 42 curriculum. The project recreates the basic behavior of bash, implementing parsing, variable expansion, signal handling, redirections, and pipes.

### 🏗️ Project Architecture

The project follows a modular architecture inspired by Norse mythology:

```
minishell/
├── includes/          # Header files
│   ├── minishell.h   # Main header
│   ├── token_tree.h  # Token and tree structures
│   ├── heimdall.h    # Execution module
│   ├── mimir.h       # Expansion module
│   ├── ratatoskr.h   # Heredoc module
│   ├── signals.h     # Signal handling
│   ├── builtins.h    # Built-in commands
│   ├── parse.h       # Parser
│   └── utils.h       # Utilities
├── src/
│   ├── main.c                # Entry point
│   ├── yggdrasil/           # Binary tree construction
│   ├── mimir/               # Variable expansion
│   ├── ratatoskr/           # Heredoc handling
│   ├── heimdall/            # Command execution
│   ├── signals/             # Odin, Hugin, Munin, Odinson
│   ├── builtins/            # cd, echo, env, exit, export, pwd, unset
│   ├── token/               # Tokenization
│   ├── parse/               # Syntax analysis
│   └── utils/               # Auxiliary functions
├── libft/             # Personal library
├── Makefile
└── valgrind.supp      # Valgrind suppressions
```

### 🔄 Execution Flow

```
User input
    ↓
[ Tokenization ]
    ↓
[ Mímir:  Variable expansion ]
    ↓
[ Ratatöskr:  Heredoc processing ]
    ↓
[ Yggdrasil: Binary tree construction ]
    ↓
[ Heimdall:  Execution ]
    ├── Bifröst: PATH search
    └── Odin, Hugin, Munin, Odinson: Signal handling
    ↓
Output / Exit status
```

### 📦 Main Components

#### 1. **Tokenization** (`src/token/`)
- Converts user input into a linked list of tokens
- Identifies metacharacters:  `|`, `<`, `>`, `<<`, `>>`
- Handles single and double quotes
- Token types: `T_CMD`, `T_PIPE`, `T_REDIR_IN`, `T_REDIR_OUT`, `T_APPEND`, `T_HEREDOC`, etc.

#### 2. **Mímir - Variable Expansion** (`src/mimir/`)
```c
int ft_mimir(t_token **token, t_data **data);
```
- Expands environment variables (`$VAR`)
- Expands `$? ` (exit status)
- Respects quote context: 
  - Single quotes: no expansion
  - Double quotes: active expansion
  - No quotes: active expansion

#### 3. **Ratatöskr - Heredoc Handling** (`src/ratatoskr/`)
```c
int ft_ratatoskr(t_token **token);
```
- Processes heredocs (`<<`)
- Creates unique temporary files (`.heredoc_N`)
- Substitutes `T_HEREDOC` with `T_REDIR_IN` pointing to temporary file
- Handles signals during reading (Ctrl+C, Ctrl+D)
- Cleans up temporary files on completion

**Process:**
1. Detects `T_HEREDOC` tokens
2. Generates unique name for temporary file
3. Reads input until delimiter (EOF) is found
4. Writes content to temporary file
5. Transforms token to `T_REDIR_IN` with temporary file
6. Configures signals (Munin) during reading

#### 4. **Yggdrasil - Binary Execution Tree** (`src/yggdrasil/`)
```c
int ft_yggdrasil(t_token **tokens, t_tree **tree, t_data **data);
```
Builds a binary execution tree where:
- **Internal nodes**:  Operators (pipes, redirections)
- **Leaf nodes**: Commands and arguments

**Tree structure:**
```
         PIPE
        /    \
      CMD1   REDIR_OUT
             /        \
           CMD2      file. txt
```

**Node types:**
- `T_PIPE`: Pipe between commands
- `T_REDIR_IN`: Input redirection (`<`)
- `T_REDIR_OUT`: Output redirection (`>`)
- `T_APPEND`: Append mode redirection (`>>`)
- `T_CMD`: External command
- `T_BUILTIN`: Built-in command

#### 5. **Heimdall - Executor** (`src/heimdall/`)
```c
int ft_heimdall(t_data **data, t_tree **ygg, char **env, int forked);
```

Executes the tree recursively according to node type: 

**a) Commands (`ft_heimdall_cmd`)**
- Checks if it's a builtin or external command
- For external commands: uses Bifröst to find the path
- Performs `fork()` and `execve()`
- Manages exit status

**b) Pipes (`ft_heimdall_pipe`)**
- Creates pipes with `pipe()`
- Forks for each side of the pipe
- Connects file descriptors
- Waits for both child processes

**c) Redirections (`ft_heimdall_redir`)**
- Opens files with appropriate flags
- Duplicates file descriptors with `dup2()`
- Executes command with redirected I/O
- Restores original descriptors

#### 6. **Bifröst - PATH Search** (`ft_bifrost`)
```c
int ft_bifrost(t_tree **ygg, char *tmp_dir);
```
- Searches for commands in PATH directories
- Verifies execution permissions with `access()`
- Handles absolute and relative paths
- Updates `tree->content[0]` with complete path

**Process:**
1. If command contains `/`, verifies directly
2. Otherwise, extracts PATH from environment
3. Iterates over each directory in PATH
4. Concatenates directory + "/" + command
5. Verifies with `access(X_OK)`
6. Returns first valid path found

#### 7. **Signal System** (`src/signals/`)

**Odin - Execution signals:**
```c
int ft_odin_signal(void);      // Ignores signals in parent process
```

**Hugin - Interactive signals:**
```c
int ft_hugin_signal(void);     // SIGINT:  new prompt line
```

**Munin - Heredoc signals:**
```c
int ft_munin_signal(void);     // SIGINT: aborts heredoc
```

**Odinson - Child process signals:**
```c
int ft_odinson_signal(void);   // Restores default signals
```

**Behavior:**
| Signal | Hugin (interactive) | Munin (heredoc) | Odin (execution) | Odinson (children) |
|--------|---------------------|-----------------|------------------|-------------------|
| SIGINT (Ctrl+C) | New line, g_status=130 | Closes heredoc | Ignored | Default (terminates) |
| SIGQUIT (Ctrl+\\) | Ignored | Ignored | Ignored | Default (core dump) |

#### 8. **Builtins** (`src/builtins/`)

Internally implemented commands:

- **`cd [path]`**: Changes directory, updates PWD and OLDPWD
- **`echo [-n] [args...]`**: Prints arguments, -n flag omits newline
- **`env`**: Displays environment variables
- **`exit [n]`**: Exits shell with code n
- **`export [VAR=value]`**: Exports/displays environment variables
- **`pwd`**: Prints current directory
- **`unset [VAR]`**: Removes environment variables

**Special features:**
- Builtins in pipes execute in subshell (forked)
- Builtins without pipe modify main shell environment
- Argument validation and error handling

### 🔧 Compilation and Usage

```bash
# Compile
make

# Execute
./minishell

# Clean
make clean    # Removes objects
make fclean   # Removes objects and binary
make re       # Recompiles from scratch
```

### 🧪 Testing

The project includes: 
- Memory handling without leaks (verified with Valgrind)
- Suppressions file for readline (`valgrind.supp`)

```bash
# Test with Valgrind
valgrind --leak-check=full --suppressions=valgrind.supp ./minishell
```

### 📝 Implemented Features

✅ **Parser:**
- Complete tokenization
- Quote handling (single and double)
- Syntax error detection
- Metacharacter support

✅ **Expansion:**
- Environment variables (`$VAR`)
- Exit status (`$?`)
- Quote context respect

✅ **Redirections:**
- Input:  `<`
- Output: `>`
- Append: `>>`
- Heredoc: `<<`

✅ **Pipes:**
- Multiple chained pipes
- Correct file descriptor handling

✅ **Signals:**
- Ctrl+C (SIGINT)
- Ctrl+D (EOF)
- Ctrl+\ (SIGQUIT)
- Context-differentiated behavior

✅ **Memory Management:**
- No memory leaks
- Correct structure freeing
- Cleanup on errors

### 🛡️ Error Handling

The project implements a robust error system:

```c
// src/errors.h
ERR_MALLOC          // Memory allocation error
ERR_SYNTAX          // Syntax error
ERR_CMD_NOT_FOUND   // Command not found
ERR_EXECVE          // Execution error
ERR_PIPE            // Pipe error
ERR_FORK            // Fork error
// ... more defined errors
```

### 🧠 Data Structures

#### Token
```c
typedef struct s_token
{
    char           *content;    // Token content
    t_type         type;        // Token type
    int            expand;      // Expansion flag
    struct s_token *next;       // Next token
    struct s_token *prev;       // Previous token
}   t_token;
```

#### Execution Tree
```c
typedef struct s_tree
{
    char          **content;    // Command and arguments
    t_type        type;         // Node type
    char          *path;        // PATH for search
    int           infile;       // Input FD
    int           outfile;      // Output FD
    pid_t         pid;          // Process PID
    struct s_tree *left;        // Left subtree
    struct s_tree *right;       // Right subtree
}   t_tree;
```

#### Main Data
```c
typedef struct s_data
{
    char    **env;              // Environment variables
    t_token *tokens;            // Token list
    t_tree  *yggdrasil;         // Execution tree
    char    *path;              // Current PATH
    int     exit_status;        // Last command exit status
    int     infile;             // Temporary input FD
    int     outfile;            // Temporary output FD
}   t_data;
```

### 🎨 Additional Features

- **Random banner** at startup (interactive mode)
- **Custom prompt**:  `bostero$> `
- **Command history** (readline)
- **Empty environment handling**:  Creates minimal environment if none exists

### 🐛 Handled Edge Cases

- Empty commands
- Multiple spaces/tabs
- Unclosed quotes
- Pipes at beginning or end
- Redirections without file
- Nonexistent variables
- Undefined PATH
- Insufficient memory
- Files without permissions
- Interrupted heredoc

### 📚 Allowed External Functions

```c
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
```

### 👥 Credits

Project developed by Juan Agustin Brosio and Ulises Novo.

---

### 🌌 May the Nine Worlds guide your shell

*"Just as Yggdrasil connects all realms, this minishell connects the user to the operating system, traversing layers of abstraction to reach the kernel itself."*

---

## 📄 License

This project is open source for educational purposes. 
