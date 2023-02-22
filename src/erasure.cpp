/**
 * \file  erasure.cpp
 * \brief Implementation of the Type Erasure Design Pattern (SBO & MVD)
 */

#include <iostream>
#include <memory>
#include <random>
#include <vector>

// TODO (update clone and move functions for SBO)
// #define SMALL_BUFFER_OPTIMISATION

/**
 * Feature Wrapper
 */
class feature {

private:

    // "Concept"
    struct FeatureNotion {

        virtual ~FeatureNotion () = default;

        // clone function: c.f. copy operations
        virtual std::unique_ptr<FeatureNotion> clone () const = 0;

        // doers
        // virtual void serialisation () const = 0;
        virtual void visualisation () const = 0;

    };

    template< typename FeatureT >
    struct FeatureModel final : public FeatureNotion {

        FeatureModel ( FeatureT i_feature )
            : m_feature { std::move( i_feature )  }
        {}

        // Prototype Design Pattern
        std::unique_ptr<FeatureNotion> clone () const override {
            return std::make_unique<FeatureModel>(*this);
        }

        /*
        void serialisation () const override {
            serialise ( m_feature );
        }
        */

        void visualisation () const override {
            visualise ( m_feature );
        }

        FeatureT m_feature;

    };


    // Extended Model: Policy-Based Design (Visualisation Strategy)
    template< typename FeatureT, typename VisualisationStr >
    struct FeatureExtendedModel final : public FeatureNotion {

        explicit FeatureExtendedModel ( FeatureT i_feature, VisualisationStr i_visualiser )
            : m_feature { std::move( i_feature ) }
            , m_visualiser { std::move( i_visualiser ) }
        {}

        void visualisation () const override {
            m_visualiser ( m_feature );
        }

        std::unique_ptr<FeatureNotion> clone () const override {
            return std::make_unique<FeatureExtendedModel>(*this);
        }

        FeatureT m_feature;
        VisualisationStr m_visualiser;

    };


    // Hidden Friends: Enablers of Dynamic Polymorphic Behaviour
    /*
    friend void serialise ( feature const& a_feature ) {
        a_feature.pimpl->serialisation ();
    }
    */

    friend void visualise ( feature const& a_feature ) {
        a_feature.pimpl->visualisation ();
    }

#ifndef SMALL_BUFFER_OPTIMISATION
    // pimpl idiom
    std::unique_ptr<FeatureNotion> pimpl;
#endif // !SMALL_BUFFER_OPTIMISATION

#ifdef SMALL_BUFFER_OPTIMISATION

    FeatureNotion* pimpl () noexcept {
        return reinterpret_cast<FeatureNotion*>( buffer.data() );
    }

    const FeatureNotion* pimpl () noexcept {
        return reinterpret_cast<const FeatureNotion*>( buffer.data() );
    } 

    // Note: avoid make_unique and its dynamic memory allocation via new
    static constexpr std::size_t BUFFER_SIZE = 128UL;
    static constexpr std::size_t ALIGNMENT = 16UL;

    alignas ( ALIGNMENT ) std::array< std::byte, BUFFER_SIZE > buffer;

#endif // SMALL_BUFFER_OPTIMISATION

public:

#ifndef SMALL_BUFFER_OPTIMISATION
    // Bridge Pattern: Templated Constructor
    template< typename FeatureT >
    feature ( FeatureT i_feature )
        : pimpl { std::make_unique<FeatureModel<FeatureT>>( std::move(i_feature) ) }
    {}

    // Note: dependency injection with visualisation strategy
    template< typename FeatureT, typename VisualisationStr >
    feature ( FeatureT i_feature, VisualisationStr i_visualiser )
        : pimpl { std::make_unique<FeatureExtendedModel<FeatureT,VisualisationStr>>( std::move(i_feature), std::move(i_visualiser) ) }
    {}

    // Copy Operations
    feature ( feature const& other )
        : pimpl { other.pimpl->clone () }
    {}

    feature& operator= ( feature const& other ) {
        other.pimpl->clone().swap( pimpl ); // copy-and-swap
        return *this;
    }

    // Move Operations
    // Note: various options available for the move operations

    // move constructor undefined (not deleted or defaulted)
    // feature ( feature&& other );

    // move assignment implemented in terms of the swap
    feature& operator= ( feature&& other ) {
        pimpl.swap ( other.pimpl );
        return *this;
    }
#endif // !SMALL_BUFFER_OPTIMISATION

#ifdef SMALL_BUFFER_OPTIMISATION

    template< typename FeatureT >
    feature ( FeatureT const& i_feature ) {
        using M = FeatureModel<FeatureT>;

        static_assert ( sizeof(M) <= BUFFER_SIZE, "oversized" );
        static_assert ( alignof(M) <= ALIGNMENT, "overaligned" );
        ::new ( pimpl() ) M ( feature );
    }

    // Special Member Functions
    ~Feature () { pimpl() -> }

#endif // SMALL_BUFFER_OPTIMISATION

    

};


void visualise ( std::vector<feature> const& feature_collection ) {
    for ( auto const& feature : feature_collection ) {
        visualise ( feature );
    }
}

// ----------------------------------------------------------------

struct location {

    explicit location ()
        : horizontal { 0. }
        , vertical { 0. }
    {}

    explicit location ( float const& h, float const& v )
        : horizontal { h }
        , vertical { v }
    {}

    float horizontal;
    float vertical;
};


class source {

public:

    source ( float const& h, float const& v, float const& s, float const& c )
        : m_size { s }
        , m_colour { c }
    {
        m_location.horizontal = h;
        m_location.vertical = v;
    }

private:

    location m_location;
    float m_size;
    float m_colour;

};

class sink {

public:

    sink ( float const& h, float const& v, float const& s, float const& c )
        : m_size { s }
        , m_colour { c }
    {
        m_location.horizontal = h;
        m_location.vertical = v;
    }

private:

    location m_location;
    float m_size;
    float m_colour;

};


void visualise ( source const& a_source ) {

}

void visualise ( sink const& a_sink ) {

}

// ----------------------------------------------------------------

int main () {

    using feature_v = std::vector<feature>;

    feature_v feature_collection;

    feature_collection.emplace_back ( source { 0.0, 0.0, 0.0, 0.0 } );
    feature_collection.emplace_back ( sink { 0.0, 0.0, 0.0, 0.0 } );
    // feature_collection.emplace_back ( source {0.0, 0.0, 0.0, 0.0}, [/*parameters*/]( source const& a_source ){/*implementation*/} );

    return EXIT_SUCCESS;   
}