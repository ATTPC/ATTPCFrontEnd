#define PADPLANEDOCK_CPP
#include <gui/PadplaneDock.hpp>
#include <gui/MainWindow.hpp>
#include <gui/DisplayFunctions.hpp>
#include <reco/Padplane.hpp>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QVBoxLayout>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace attpcfe {

  class PadplaneDock::PadplaneDockImpl {

  public:
    PadplaneDockImpl(QWidget* parent) : _mainWindow{dynamic_cast<MainWindow*>(parent)} {}

    MainWindow* _mainWindow;

    // Handles to widgets PadplaneDock took ownership of
    QPushButton* _loadButton{nullptr};
    QPushButton* _showButton{nullptr};

    // State of PadplaneDock
    std::unique_ptr<Padplane> _pPadplane;
  };

  PadplaneDock::PadplaneDock(QWidget* parent) : QDockWidget{parent}, _pImpl{new PadplaneDockImpl{parent}, [](PadplaneDockImpl* ptr){ delete ptr; }}
  {
    setWindowTitle(tr("Padplane Display"));
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setFixedSize(200, 200);

    auto layout = new QVBoxLayout{};
    _pImpl->_loadButton = new QPushButton{"Load"};
    layout->addWidget(_pImpl->_loadButton);
    connect(_pImpl->_loadButton, &QPushButton::clicked, this, &PadplaneDock::load);
    _pImpl->_showButton = new QPushButton{"Show"};
    layout->addWidget(_pImpl->_showButton);
    connect(_pImpl->_showButton, &QPushButton::clicked, this, &PadplaneDock::show);
    layout->addStretch();

    auto widget = new QWidget{};
    widget->setLayout(layout);
    setWidget(widget);
  }

  void PadplaneDock::load()
  {
    QFileDialog dialog{this};
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Padplane geometry (*.geom)"));
    dialog.setViewMode(QFileDialog::Detail);
    if (dialog.exec())
    {
      _pImpl->_pPadplane = std::make_unique<Padplane>(dialog.selectedFiles().front().toStdString());

      std::ifstream in{_pImpl->_pPadplane->geomFile()};

      std::size_t padNum;
      double x_0, x_1;
      double y_0, y_1;
      std::string line;
      while (std::getline(in, line))
      {
	std::istringstream s{line};
	s >> padNum >> x_0 >> y_0 >> x_1 >> y_1;

	((x_1 - x_0) < _pImpl->_pPadplane->sPadSize()) ?
	  _pImpl->_pPadplane->sPadCoords()[padNum] = {x_0, y_0} :
	  _pImpl->_pPadplane->lPadCoords()[padNum] = {x_0, y_0};
	
	if (y_1 > y_0) _pImpl->_pPadplane->orientations()[padNum] = 1;
      }
    }
    else
    {
      std::cout << "> PadplaneDock::load, message: a padplane geometry file (.geom) must be selected\n";
    }
  }

  void PadplaneDock::show()
  {
    if (_pImpl->_pPadplane != nullptr)
    {
      display(_pImpl->_mainWindow->padPlaneDisplay(), _pImpl->_pPadplane.get());
    }
    else
    {
      std::cout << "> PadplaneDock::show, message: a padplane geometry file (.geom) must be loaded first\n";
    }
  }
  
}
