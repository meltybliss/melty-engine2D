#include "editor/CommandStack.h"

void CommandStack::Do(std::unique_ptr<ICommand> cmd) {
	if (!cmd) return;
	cmd->Execute();	
	undoStack.push_back(std::move(cmd));
	redoStack.clear();
}


void CommandStack::Undo() {
	if (undoStack.empty()) return;

	auto cmd = std::move(undoStack.back());
	undoStack.pop_back();

	cmd->Undo();
	redoStack.push_back(std::move(cmd));
}


void CommandStack::Redo() {
	if (redoStack.empty()) return;

	auto cmd = std::move(redoStack.back());
	redoStack.pop_back();

	cmd->Execute();
	undoStack.push_back(std::move(cmd));

}


void CommandStack::Clear() {
	undoStack.clear();
	redoStack.clear();
}