#ifndef FILTERCONTAINER_H
#define FILTERCONTAINER_H

#include <QList>
#include <QQmlListProperty>

class Filter;
class QQmlSortFilterProxyModel;

class  FilterContainer {
public:
    virtual ~FilterContainer();

    QList<Filter*> filters() const;
    void appendFilter(Filter* filter);
    void removeFilter(Filter* filter);
    void clearFilters();

    QQmlListProperty<Filter> filtersListProperty();

protected:
    QList<Filter*> m_filters;

private:
    virtual void onFilterAppended(Filter* filter) = 0;
    virtual void onFilterRemoved(Filter* filter) = 0;
    virtual void onFiltersCleared() = 0;

    static void append_filter(QQmlListProperty<Filter>* list, Filter* filter);
    static int count_filter(QQmlListProperty<Filter>* list);
    static Filter* at_filter(QQmlListProperty<Filter>* list, int index);
    static void clear_filters(QQmlListProperty<Filter>* list);
};



#define FilterContainer_iid "fr.grecko.SortFilterProxyModel.FilterContainer"
Q_DECLARE_INTERFACE(FilterContainer, FilterContainer_iid)

#endif // FILTERCONTAINER_H
