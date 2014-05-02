#pragma once

#include "MSACore.h"
#include "MSAPhysicsConstraint.h"


namespace msa {
	
	namespace physics {
		
		template <typename T>
		class SpringT : public ConstraintT<T> {
		public:
			friend class WorldT<T>;
			
			SpringT(ParticleT<T>* a, ParticleT<T>* b, float strength, float restLength) {
				this->_a	= a;
				this->_b	= b;
				this->_type = kConstraintTypeSpring;
				this->setClassName("SpringT");
				
				setStrength(strength);
				setRestLength(restLength);
				setForceCap(0);
                setID(0);
			
			
            ParticleT<T>* getParticleA();
            ofVec3f getParticlePositionA();
            ParticleT<T>* getParticleB();
			ofVec3f getParticlePositionB();
            
            void setID(int id);
            int getID();
            
			void setStrength(float s);
			float getStrength();
			
			void setForceCap (float c);
			float getForceCap ();
			
			void setRestLength(float l);
			float getRestLength();

			
			
		protected:
			float _restLength;
			float _strength;
			float _forceCap;
			int ID;
			
			void solve() {
				T delta = this->_b->getPosition() - this->_a->getPosition();
				float deltaLength2 = delta.lengthSquared();
				float deltaLength = sqrt(deltaLength2);	// TODO: fast approximation of square root (1st order Taylor-expansion at a neighborhood of the rest length r (one Newton-Raphson iteration with initial guess r))
				float force = deltaLength > 0 ? _strength * (deltaLength - _restLength) / (deltaLength * (this->_a->getInvMass() + this->_b->getInvMass())) : 0;
				
				
				T deltaForce = delta * force;
				
				if (_forceCap > 0)
					deltaForce.limit(_forceCap);
				
				if (this->_a->isFree()) this->_a->moveBy(deltaForce * this->_a->getInvMass(), false);
				if (this->_b->isFree()) this->_b->moveBy(deltaForce * -this->_b->getInvMass(), false);
			}
			
			
			void debugDraw() {
				ConstraintT<T>::debugDraw();
			}
			
		};
		
        //--------------------------------------------------------------
		template <typename T>
		inline ParticleT<T>* SpringT<T>::getParticleA() {
			//_strength = s;
            return this->_a;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		inline ofVec3f SpringT<T>::getParticlePositionA() {
			//_strength = s;
            return this->_a->getPosition();
		}
        
        //--------------------------------------------------------------
		template <typename T>
		inline ParticleT<T>* SpringT<T>::getParticleB() {
			//_strength = s;
            return this->_b;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		inline ofVec3f SpringT<T>::getParticlePositionB() {
			//_strength = s;
            return this->_b->getPosition();
		}
        
        //--------------------------------------------------------------
		template <typename T>
		inline void SpringT<T>::setID(int id) {
			ID = id;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		inline int SpringT<T>::getID() {
			return ID;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		inline void SpringT<T>::setStrength(float s) {
			_strength = s;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		inline float SpringT<T>::getStrength() {
			return _strength;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		inline void SpringT<T>::setForceCap(float c) {
			_forceCap = c;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		inline float SpringT<T>::getForceCap() {
			return _forceCap;
		}
		
		
        //--------------------------------------------------------------
		template <typename T>
		inline void SpringT<T>::setRestLength(float l) {
			_restLength = l;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		inline float SpringT<T>::getRestLength() {
			return _restLength;
		}
		
		
	}
}