#ifndef FINDERIMPL_H
#define FINDERIMPL_H

#include <QObject>
#include <Finder.h>
class FinderImpl : public QObject, public Finder
{
	Q_OBJECT

public:
	FinderImpl(QObject *parent);
    void getAllFiles(std::string sRoot, std::list<Info>& lstNames) override;
	~FinderImpl();

private:
    void findFiles(std::string sRoot, std::list<Info>& lstNames);
};

#endif // FINDERIMPL_H
