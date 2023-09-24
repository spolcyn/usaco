"""
ID: sp.shop1
LANG: PYTHON3
TASK: namenum
"""

# From the analysis: Core improvement is that instead of looking up the words in
# the dictionary, you can look up the dictionary in the words (b/c len(dict) <<
# len(words))

# 12-digit serial number, possible words = 3^12 (500K)
# That's a lot of lookups
from pathlib import Path
from collections import defaultdict
from dataclasses import dataclass, field
from typing import Optional

from itertools import product


@dataclass
class Node:
    val: str
    is_endpoint: bool = False
    children: dict = field(default_factory=defaultdict)

    @classmethod
    def from_val(cls, val: str):
        node = cls(val)
        return node

    def add_child(self, val: str) -> "Node":
        if val not in self.children:
            self.children[val] = Node(val=val)
        return self.children[val]

    def get_child(self, val: str) -> Optional["Node"]:
        return self.children.get(val)


class Trie:
    def __init__(self):
        self.root = Node(val="*")

    def add_word(self, word: str):
        next_node = self.root
        for c in word:
            next_node = next_node.add_child(c)

        next_node.is_endpoint = True

    def word_exists(self, word: str):
        next_node = self.root
        for c in word:
            next_node = next_node.get_child(c)
            if next_node is None:
                return False

        return next_node.is_endpoint


number_to_letters: dict[str, list[str]] = {
    "2": ["A", "B", "C"],
    "3": ["D", "E", "F"],
    "4": ["G", "H", "I"],
    "5": ["J", "K", "L"],
    "6": ["M", "N", "O"],
    "7": ["P", "R", "S"],
    "8": ["T", "U", "V"],
    "9": ["W", "X", "Y"],
}


word_tree: Trie = Trie()

possible_names_file: Path = Path("dict.txt")
for name in possible_names_file.read_text().splitlines():
    word_tree.add_word(name)

serial: str = Path("namenum.in").read_text().strip()
letter_possibilities: list[list[str]] = [number_to_letters[c] for c in serial]
words = product(*letter_possibilities)

with open("namenum.out", mode="w") as f:
    have_matches: bool = False
    for word in words:
        word = "".join(word)
        if word_tree.word_exists(word):
            have_matches = True
            f.write(f"{word}\n")

    if not have_matches:
        f.write("NONE\n")

