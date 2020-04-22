//
//  Registry.hpp
//  Loom-Deconstructed
//
//  Created by Eli Winkelman on 4/21/20.
//

#ifndef Registry_hpp
#define Registry_hpp

/// Import anything you might include in the factory here:

///////////////////////////////////////////////////////////////////////////////
///Forward declare any classes that will be served to created objects
class Scope;

/// Creates a new T, returned as S*. S must be base of T
/// @return The created T
template<class S, class T> S* ConstructDefault() { return new T(); }

/// Creates a new T, returned as S*. S must be base of T
/// @return The created T
/*template<class S, class T> S* ConstructDefaultJson(JsonArrayConst p) { return new T(p); }*/

///
template <typename T, typename ... Ts>
class Registry {
public:
    
    static T* create(const char* name, Scope* scope) {
        return nullptr;
    }
    
    /*static T* create(JsonVariant target, Scope* scope) {
        return nullptr;
    }*/
    
};

template <typename T, typename U, typename ... Ts>
class Registry<T, U, Ts...> : Registry<T, Ts...> {
    using FactoryFunction = T*(*)();
    using FactoryPair = std::pair<char*, FactoryFunction>;
    
public:

    static T* create(const char* name, Scope* scope) {
        if (!strcmp(name, U::name)) {
            return ConstructDefault<T, U>();
        }
        return Registry<T, Ts...>::create(name, scope);
    }
    
    /*
    static T* create(JsonVariant target, Scope* scope) {
        const char* name = target["name"].as<char*>();
        
        if (!strcmp(name, U::name)) {
            return ConstructDefaultJson<T, U>(target);
        }
        return Registry<T, Ts...>::create(target, scope);
    }*/
};


#endif /* Registry_hpp */
