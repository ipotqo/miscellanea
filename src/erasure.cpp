/**
 * \file  erasure.cpp
 * \brief Implementation of the Type Erasure Design Pattern
 */

#include <iostream>

/**
 * Feature Wrapper
 */
class feature {

private:

    // "Concept"
    struct FeatureNotion {

        virtual ~FeatureNotion () = default;

        virtual void serialisation () const = 0;
        virtual void visualisation () const = 0;

    };

    template< typename FeatureT >
    struct FeatureModel : public FeatureNotion {

        FeatureModel ( FeatureT i_feature )
            : m_feature { std::move( i_feature )  }
        {}

        void serialisation () const override {
            serialise ( m_feature );
        }

        void visualisation () const override {
            visualise ( m_feature );
        }

        FeatureT m_feature;

    };

    // pimpl idiom
    std::unique_ptr<FeatureNotion> pimpl;

public:

    template< typename FeatureT >
    feature ( FeatureT i_feature )
        : pimpl { std::make_unique<FeatureModel<FeatureT>>( std::move(i_feature) ) }
    {}

    // Copy Operations
    feature ( feature const& other );
    feature& operator= ( feature const& other );

    // Move Operations
    feature ( feature&& other );
    feature& operator= ( feature&& other );

};


int main () {



    return EXIT_SUCCESS;   
}