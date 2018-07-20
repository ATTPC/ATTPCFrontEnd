#define TPCDOCK_CPP
#include <gui/TpcDock.hpp>
#include <gui/MainWindow.hpp>
#include <gui/DisplayFunctions.hpp>
#include <reco/Tpc.hpp>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QVBoxLayout>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace attpcfe {

  class TpcDock::TpcDockImpl {

  public:
    TpcDockImpl(QWidget* parent) : _mainWindow{dynamic_cast<MainWindow*>(parent)} {}

    MainWindow* _mainWindow;

    // Handles to widgets TpcDock took ownership of
    QPushButton* _loadButton{nullptr};
    QPushButton* _showButton{nullptr};

    // State of TpcDock
    std::unique_ptr<Tpc> _pTpc;
  };

  TpcDock::TpcDock(QWidget* parent) : QDockWidget{parent}, _pImpl{new TpcDockImpl{parent}, [](TpcDockImpl* ptr){ delete ptr; }}
  {
    setWindowTitle(tr("Tpc Display"));
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setFixedSize(200, 200);

    auto layout = new QVBoxLayout{};
    _pImpl->_loadButton = new QPushButton{"Load"};
    layout->addWidget(_pImpl->_loadButton);
    connect(_pImpl->_loadButton, &QPushButton::clicked, this, &TpcDock::load);
    _pImpl->_showButton = new QPushButton{"Show"};
    layout->addWidget(_pImpl->_showButton);
    connect(_pImpl->_showButton, &QPushButton::clicked, this, &TpcDock::show);
    layout->addStretch();

    auto widget = new QWidget{};
    widget->setLayout(layout);
    setWidget(widget);
  }

  void TpcDock::load()
  {
    QFileDialog dialog{this};
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("TPC geometry (*.geom)"));
    dialog.setViewMode(QFileDialog::Detail);
    if (dialog.exec())
    {
      _pImpl->_pTpc = std::make_unique<Tpc>(dialog.selectedFiles().front().toStdString());

      std::ifstream in{_pImpl->_pTpc->geomFile()};

      auto radius = 0.;
      auto height = 0.;
      std::string line;
      while (std::getline(in, line))
      {
	std::istringstream s{line};
	s >> radius >> height;

	_pImpl->_pTpc->setRadius(radius);
	_pImpl->_pTpc->setHeight(height);
      }
    }
    else
    {
      std::cout << "> TpcDock::load, message: a TPC geometry file (.geom) must be selected\n";
    }
  }

  void TpcDock::show()
  {
    if (_pImpl->_pTpc != nullptr)
    {
      display(_pImpl->_mainWindow->tpcDisplay(), _pImpl->_pTpc.get());
    }
    else
    {
      std::cout << "> TpcDock::show, message: a TPC geometry file (.geom) must be loaded first\n";
    }
  }
  
}
