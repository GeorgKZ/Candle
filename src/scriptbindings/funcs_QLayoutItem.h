  // virtual QSize sizeHint() const
  Q_INVOKABLE virtual wrapper_QSize *sizeHint() const;

  // virtual QSize minimumSize() const
  Q_INVOKABLE virtual wrapper_QSize *minimumSize() const;

  // virtual QSize maximumSize() const
  Q_INVOKABLE virtual wrapper_QSize *maximumSize() const;

  // virtual Qt::Orientations expandingDirections() const
  Q_INVOKABLE virtual Qt::Orientations expandingDirections() const;

//  /*Q_INVOKABLE*/ virtual void setGeometry(const wrapper_QRect&);

//  /*Q_INVOKABLE*/ virtual wrapper_QRect *geometry() const;

  Q_INVOKABLE virtual bool isEmpty() const;

  Q_INVOKABLE virtual bool hasHeightForWidth() const;

  Q_INVOKABLE virtual int heightForWidth(int width) const;

  Q_INVOKABLE virtual int minimumHeightForWidth(int width) const;

  /*Q_INVOKABLE*/ virtual void invalidate();

  // virtual QWidget *widget() const;
  Q_INVOKABLE virtual QJSValue widget() const;

  // virtual QLayout *layout();
  Q_INVOKABLE virtual QJSValue layout();

  // virtual QSpacerItem *spacerItem();
//  Q_INVOKABLE virtual wrapper_QSpacerItem *spacerItem();

  // Qt::Alignment alignment() const
  Q_INVOKABLE Qt::Alignment alignment() const;

  // void setAlignment(Qt::Alignment a)
  Q_INVOKABLE void setAlignment(Qt::Alignment a);

  // virtual QSizePolicy::ControlTypes controlTypes() const
  // Q_INVOKABLE virtual wrapper_QSizePolicy::ControlTypes controlTypes() const;
