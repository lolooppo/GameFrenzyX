from abc import ABC, abstractmethod


class IPage(ABC):

    @abstractmethod
    def run(self):
        pass