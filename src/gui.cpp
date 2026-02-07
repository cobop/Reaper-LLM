#include "gui.h"
#include <QVBoxLayout>
#include <QLabel>

ReaperLLMGui::ReaperLLMGui(QWidget* parent) : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Reaper‑LLM Plugin", this));
    // Future UI: API key fields, prompt input, status display
}

ReaperLLMGui::~ReaperLLMGui() = default;
