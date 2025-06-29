class KMP:
    def __init__(self, needle) -> None:
        self.needle = needle
        self.n = len(needle)
        self.pi = self.piTable()

    def piTable(self):
        pi = [0] * self.n
        for i in range(1, self.n):
            j = pi[i - 1]
            while j and self.needle[i] != self.needle[j]:
                j = self.pi[j - 1]
            pi[i] = j + 1 if self.needle[i] == self.needle[j] else 0
        return pi

    def strStr(self, haystack: str, needle: str) -> int:
        nl, hl = len(needle), len(haystack)
        pi = self.piTable()
        needleptr = 0
        matching_indices = []
        for hayptr in range(hl):
            # if a mismatch was found, roll back the needle
            while needleptr and needle[needleptr] != haystack[hayptr]:
                needleptr = pi[needleptr - 1]
            # match move the needle forward
            if haystack[hayptr] == needle[needleptr]:
                needleptr += 1
            # found a complete match
            if needleptr == nl:
                matching_indices.append(hayptr - needleptr)
                # roll back to last matching
                needleptr = pi[needleptr - 1]
        return -1
