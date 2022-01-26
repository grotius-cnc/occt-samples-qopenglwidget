// Copyright (c) 2021 OPEN CASCADE SAS
//
// This file is part of the examples of the Open CASCADE Technology software library.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE

#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>

#include <QAction>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>


#include <Standard_WarningsRestore.hxx>
#include <Standard_Version.hxx>
#include <Standard_WarningsDisable.hxx>

#include "OcctQtViewer.h"

//! Main application window.
class MyMainWindow : public QMainWindow
{
  OcctQtViewer* myViewer;
public:
  MyMainWindow() : myViewer (nullptr)
  {
    {
      // menu bar with Quit item
      QMenuBar* aMenuBar = new QMenuBar();
      QMenu* aMenuWindow = aMenuBar->addMenu ("&File");
      QAction* anActionAbout = new QAction (aMenuWindow);
      anActionAbout->setText ("Quit");
      aMenuWindow->addAction (anActionAbout);
      connect (anActionAbout, &QAction::triggered, [this]()
      {
        close();
      });
      setMenuBar (aMenuBar);
    }
    {
      // 3D Viewer and some controls on top of it
      myViewer = new OcctQtViewer();
      QVBoxLayout* aLayout = new QVBoxLayout (myViewer);
      aLayout->setDirection (QBoxLayout::BottomToTop);
      aLayout->setAlignment (Qt::AlignBottom);
      {
        QPushButton* aQuitBtn = new QPushButton ("About");
        aLayout->addWidget (aQuitBtn);
        connect (aQuitBtn, &QPushButton::clicked, [this]()
        {
          QMessageBox::information (0, "About Sample", QString()
                                  + "OCCT 3D Viewer sample embedded into Qt Widgets.\n\n"
                                  + "Open CASCADE Technology v." OCC_VERSION_STRING_EXT "\n"
                                  + "Qt v." QT_VERSION_STR "\n\n"
                                  + "OpenGL info:\n"
                                  + myViewer->getGlInfo());
        });

        QPushButton* aQuitBtn1 = new QPushButton ("Test");
        aLayout->addWidget (aQuitBtn1);
        connect (aQuitBtn1, &QPushButton::clicked, [this]()
        {
          //! A example how to call opengl.
          OcctQtViewer().draw_opengl();
        });


      }
      {
        QWidget* aSliderBox = new QWidget();
        QHBoxLayout* aSliderLayout = new QHBoxLayout (aSliderBox);
        {
          QLabel* aSliderLabel = new QLabel ("Background");
          aSliderLabel->setStyleSheet ("QLabel { background-color: rgba(0, 0, 0, 0); color: white; }");
          aSliderLabel->setGeometry (50, 50, 50, 50);
          aSliderLabel->adjustSize();
          aSliderLayout->addWidget (aSliderLabel);
        }
        {
          QSlider* aSlider = new QSlider (Qt::Horizontal);
          aSlider->setRange (0, 255);
          aSlider->setSingleStep (1);
          aSlider->setPageStep (15);
          aSlider->setTickInterval (15);
          aSlider->setTickPosition (QSlider::TicksRight);
          aSlider->setValue (0);
          aSliderLayout->addWidget (aSlider);
          connect (aSlider, &QSlider::valueChanged, [this](int theValue)
          {
            const float aVal = theValue / 255.0f;
            const Quantity_Color aColor (aVal, aVal, aVal, Quantity_TOC_sRGB);
            //myViewer->View()->SetBackgroundColor (aColor);
            myViewer->View()->SetBgGradientColors (aColor, Quantity_NOC_BLACK, Aspect_GFM_DIAG1);
            myViewer->View()->Invalidate();
            myViewer->update();
          });
        }
        aLayout->addWidget (aSliderBox);
      }
      setCentralWidget (myViewer);
    }
  }
};

int main (int theNbArgs, char** theArgVec)
{
  QApplication aQApp (theNbArgs, theArgVec);

  QCoreApplication::setApplicationName ("OCCT Qt Viewer sample");
  QCoreApplication::setOrganizationName ("OpenCASCADE");
  QCoreApplication::setApplicationVersion (OCC_VERSION_STRING_EXT);

  MyMainWindow aMainWindow;
  aMainWindow.resize (aMainWindow.sizeHint());
  aMainWindow.show();
  return aQApp.exec();
}
