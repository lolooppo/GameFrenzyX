from abc import ABC, abstractmethod


class IPage(ABC):

    """Interface for all page implementations"""
    @abstractmethod
    def run(self):
        pass
