# 🎮 Terminal Trivia

A small terminal-based general trivia drinking game designed for fun amongst friends. 

---

## 🛠 Compilation

- Developed in **VS Code** using **C**.
- Compiled and run in **WSL2**.

```bash
# Debug information
make debug

# Final build
make release
```

---

## 📦 Dependencies

This project requires the following dependency:

- **`aplay`**: Used for audio playback functionality. Ensure `aplay` is installed and accessible in your environment.

---

## ✨ Features

- 🎨 **Supports up to 20 players** with unique identifying colors.
- 📊 **Scoreboard tracking** to keep track of player points throughout the game.
- 🔒 **Hidden character entry** for private and secure answer submissions.
- ⚙️ **Linked list-based data structures** for efficient handling of players and questions:
  - **QNode**: Manages attributes for trivia questions.
  - **Node**: Manages attributes for players.

---

## 🚀 Getting Started

### Prerequisites
Before you begin, ensure you have the following installed:
- **gcc**: The GNU Compiler Collection
- **make**: Build tool for compiling the project
- **aplay**: For audio playback

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/comfyy-dev/trivia.git
   ```

2. Navigate to the project directory:
   ```bash
   cd terminal-trivia
   ```

3. Compile the code:
   ```bash
   make release
   ```

4. Run the game:
   ```bash
   ./terminal_trivia
   ```

---

## 💡 How to Play

1. **Prepare Questions**: Create a .txt file which has the questions and answers as shown in *example.txt* and ensure the MakeFile compiles it as the argument.
2. **Start the Game**: After running the game, follow the on-screen instructions to set up players and start the trivia.
3. **Enter Answers Privately**: Each player sends their answers privately and the admin enters it, and scores are updated automatically.
4. **Track Scores**: Players who answer correctly are assigned answers, and the scoreboard keeps track of everyone's progress in real-time.
5. **Side Activities**: Admin can choose whether or not to introduce fun side rules or activities of your own choice.

---

## 🤝 Contributing

Contributions are always welcome!  

### Steps to Contribute:
1. Fork the repository.
2. Create a new branch (`git checkout -b feature-name`).
3. Make your changes and commit them (`git commit -m 'Add a feature'`).
4. Push to the branch (`git push origin feature-name`).
5. Submit a pull request.

---


## 📬 Contact

Developed by **Your Name**  
- Email: [comfyy.content@gmail.com](mailto:comfyy.content@gmail.com)  
- GitHub: [https://github.com/comfyy-dev](https://github.com/comfyy-dev)

---

## 🎉 Acknowledgments

- Inspired by my friends.
- Thanks to all contributors and testers for their feedback and support.
