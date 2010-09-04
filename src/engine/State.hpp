#ifndef STATE_HPP
#define STATE_HPP

namespace Engine{

class State{
public:
    State();
    virtual ~State() = 0;


    virtual void Update(const float time_delta);
    void UpdateAllEntities(const float time_delta);

    // Draws all entities to render target.
    void Draw(const sf::RenderTarget* const target) const;

    void AddEntity(const Entity& entity);

private:
    Root* mRoot;

    // Entity list
    boost::ptr_vector<Entity> mEntities;
    // Saves if there are new Entities, so the list has to be sorted for correct order while drawing.
    bool mEntityListNeedsSorting;


};

}

#endif
