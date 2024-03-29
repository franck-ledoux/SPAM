/*---------------------------------------------------------------------------*/
#ifndef MATCHING_IACTION_H
#define MATCHING_IACTION_H
/*---------------------------------------------------------------------------*/
struct IAction {
    virtual ~IAction() = default;
    virtual bool operator==(const IAction& other) const = 0;
};
/*---------------------------------------------------------------------------*/
#endif //MATCHING_IACTION_H
/*---------------------------------------------------------------------------*/
