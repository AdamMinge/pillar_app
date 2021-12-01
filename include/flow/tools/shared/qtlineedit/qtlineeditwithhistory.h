#ifndef FLOW_TOOLS_LINE_EDIT_WITH_HISTORY_H
#define FLOW_TOOLS_LINE_EDIT_WITH_HISTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLineEdit>
#include <QStringList>
/* -------------------------------------------------------------------------- */

namespace tools
{

  class TOOLS_SHARED_API QtLineEditWithHistory : public QLineEdit
  {
  Q_OBJECT

  public:
    explicit QtLineEditWithHistory(QWidget* parent = nullptr);
    ~QtLineEditWithHistory() override;

  public Q_SLOTS:
    void appendToHistory(QString text);

    void setHistory(QStringList history);
    [[nodiscard]] QStringList getHistory() const;

    void move(qsizetype direction);
    void moveNext();
    void movePrev();

  private:
    QStringList m_history;
    qsizetype m_history_position;
  };

} // namespace tools

#endif //FLOW_TOOLS_LINE_EDIT_WITH_HISTORY_H
