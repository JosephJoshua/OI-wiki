author: cutekibry, woruo27, Backl1ght, c-forrest

**Game theory** is a branch of economics. It studies individuals who compete with or oppose each other, and the behavior that results under specific rules. Game theory looks at both the expected behavior and the actual behavior of individuals in a game, and studies their optimal strategies.

Put simply, game theory studies how several players in a game choose their strategies.

## Basic concepts

This section gives a short introduction to some common concepts in game theory.

### Cooperative/non-cooperative games

A **cooperative game** is a game in which the players can form alliances and work together. In such games, a player who refuses to cooperate is usually punished by some outside mechanism. In contrast, a **noncooperative game** has no such mechanism, so the players either cannot form alliances at all, or can only keep cooperation going through credible threats.

Noncooperative games have been studied more systematically and in more depth than cooperative games. All games discussed in this article are noncooperative games.

### Symmetric/asymmetric games

In a **symmetric game**, different players get the same payoff when they take the same action. In other words, the payoff depends only on the action itself, not on who takes it. A game that does not satisfy this condition is called an **asymmetric game**.

### Zero-sum/non-zero-sum games

Main page: [Zero-sum games](./zero-sum-game.md)

A **zero-sum game** is a game in which the payoffs of all players always add up to zero, no matter what actions they take. Zero-sum games usually involve two players, so one player's gain is always the other player's loss. In contrast, a **non-zero-sum game** allows all sides to win together or lose together. Examples include the **positive-sum game** and the **negative-sum game**.

### Simultaneous/sequential games

In a **simultaneous game**, all players make their decisions at the same time without knowing what the others choose. Rock paper scissors is a typical simultaneous game. Such games are often described with a payoff matrix, and usually do not involve the idea of time.

The opposite is a **sequential game**, where players act one after another. Note that later players must be able to see at least part of what earlier players did; otherwise the order would not matter at all. Sequential games are usually described with a game tree.

### Perfect/imperfect information games

**Perfect information** means that whenever a player makes a decision, they know everything that has happened before, including the initial state of the game. For example, chess and Go are perfect information games, while mahjong and poker are imperfect information games, because a player cannot see the other players' hands. Perfect information is usually used to describe sequential games. In a simultaneous game, players cannot know what the others are about to do, so simultaneous games are usually not considered perfect information games.

### Complete/incomplete information games

**Complete information** means that every player fully knows the structure of the game itself (including every player's possible decisions and final payoffs), and this information is **common knowledge**. The opposite is an incomplete information game, where some parts of the game (such as an opponent's possible decisions or payoff function) are unknown to a player.

Note that "complete information" and "perfect information" are two independent concepts, and neither one implies the other. For example, mahjong is a game with complete but imperfect information: its rules and payoffs are public, but the tiles are hidden. On the other hand, some games where players have hidden goals, but every action is public, are games with perfect but incomplete information.

## Combinatorial game theory

In competitive programming, the most common type of game is the **combinatorial game**. The term usually refers to games that are hard to solve because they have a huge number of states. Since general combinatorial games are very complicated, combinatorial game theory mainly focuses on this type: two-player games where the players take turns, with perfect information and no randomness. Chess and Go are typical combinatorial games.

### Impartial games

Main page: [Impartial games](./impartial-game.md)

An **impartial game** is a combinatorial game that satisfies these conditions:

-   In any given state, all players have exactly the same set of possible moves. The moves depend only on the current state, not on who is moving;
-   The same state can never be reached twice. The game ends when a player cannot move, and the game always ends after a finite number of moves without a draw.

Impartial games are always symmetric games.

### Partizan games

Main page: [Partizan games](./partizan-game.md)

The opposite of an impartial game is a **partizan game**, in which the moves available to a player in a state depend on who the player is. Most board games (such as chess, Chinese chess (xiangqi), Go and gomoku) are partizan games, because each player can only move their own pieces.

### Normal/misère play

In a combinatorial game, the winner is usually the last player to make a move before the game ends. This is called **normal play** (a normal game). The opposite is **misère play** (a misère game), where the last player to make a move before the game ends is the loser.

Both impartial and partizan games can be played under either normal or misère rules.

## References

-   [Game theory - Wikipedia](https://en.wikipedia.org/wiki/Game_theory)
-   [Combinatorial game theory - Wikipedia](https://en.wikipedia.org/wiki/Combinatorial_game_theory)
-   [Impartial game - Wikipedia](https://en.wikipedia.org/wiki/Impartial_game)
-   [Misère - Wikipedia](https://en.wikipedia.org/wiki/Mis%C3%A8re)
