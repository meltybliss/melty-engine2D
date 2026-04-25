#pragma once
#include "ICommand.h"
#include <memory>
#include <vector>

class CommandStack {
public:

	void Do(std::unique_ptr<ICommand> cmd);

	void Undo();
	void Redo();

	void Clear();

private:
	std::vector<std::unique_ptr<ICommand>> undoStack;
	std::vector<std::unique_ptr<ICommand>> redoStack;

};