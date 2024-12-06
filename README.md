# Turing Machine in C

This repository contains an implementation of a **Turing Machine** written in C. A Turing Machine is a mathematical model of computation that manipulates symbols on a strip of tape according to a table of rules. It is used to understand the limits of what can be computed.

## Features

- **Flexible Tape Initialization**: Random, default, or user-defined initial tape configurations.
- **Customizable Instructions**: Supports user-defined transition states through input files.
- **Execution Logging**: Outputs tape state and head position during execution.
- **Memory Management**: Dynamically expands the tape as needed.


## Usage

### Build Instructions

Compile the code using GCC or any compatible C compiler:

```bash
gcc -o turing_machine turing_machine.c
```

### Running the Program

#### Syntax:
```bash
./turing_machine <instruction_file.turing> <optional_initial_tape>
```

- `<instruction_file.turing>`: File containing Turing Machine instructions.
- `<optional_initial_tape>`: (Optional) Initial tape configuration.

#### Example:
1. With default tape:
   ```bash
   ./turing_machine instructions.turing
   ```

2. With custom tape:
   ```bash
   ./turing_machine instructions.turing "11001"
   ```

### Input File Format

The `.turing` instruction file should follow the format:
```
<state> <expected_symbol> <write_symbol> <direction> <next_state>
```

- **state**: The current state (integer).
- **expected_symbol**: Symbol to read at the head.
- **write_symbol**: Symbol to write at the head.
- **direction**: Direction to move the head (`R`, `L`, or `H` for Halt).
- **next_state**: Next state to transition to.

#### Example:
```
0 _ 1 R 1
1 1 0 L 0
1 _ _ H 0
```

### Outputs

- Final tape state.
- Head position.
- Error messages for out-of-bound conditions or invalid instructions.

---



## Limitations

- The tape must have sufficient memory; expansion occurs dynamically but is limited by system constraints.
- Instructions must cover all possible states and symbols to avoid runtime errors.

---

## Contributing

1. Fork the repository.
2. Create a new feature branch: `git checkout -b feature-name`.
3. Commit your changes: `git commit -m "Add feature-name"`.
4. Push to the branch: `git push origin feature-name`.
5. Open a Pull Request.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

