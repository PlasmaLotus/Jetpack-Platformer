#include "EventManager.h"


EventManager::EventManager(void)
{
}


EventManager::~EventManager(void)
{
}

void EventManager::_connect(const void* subject, const Parcel& parcel){
	bool sameEventFound = false;
	bool sameParcelFound = false;
	for(auto it = map.begin(); it != map.end(); ++it){
		const void* __subject = it->first;
		if(subject == __subject){
			sameEventFound = true;
			List& list = it->second;
			
			for(auto pIt = list.begin(); pIt != list.end(); ++pIt){
				Parcel& p(*pIt);
				if(parcel._event == pIt->_event ||
					parcel._receiver == pIt->_receiver ||
					parcel._member_callback == pIt->_member_callback ||
					parcel._lonely_callback == pIt->_lonely_callback ){
					sameParcelFound = true;
				}

			}//for
			if(!sameParcelFound){
				//add parcel;
				list.push_back(parcel);
			}
		}
	}//for

	if(!sameEventFound){
		if(!sameParcelFound){
			List list;
			list.push_back(parcel);
			map.insert(std::pair<const void*, List>(subject, list));
		}
	}
}

bool EventManager::_disconnect (const void*subject, const Parcel& parcel){
	//return false;
	bool subjectFound = false;
	bool parcelFound = false;
		for(auto it = map.begin(); it != map.end(); ++it){
		const void* __subject = it->first;
		if(subject == __subject){
			subjectFound = true;
			List& list = it->second;
			//bool sameParcelFound = false;
			for(auto pIt = list.begin(); pIt != list.end(); ++pIt){
				Parcel& p = *pIt;
				if(parcel._event == p._event ||
					parcel._receiver == p._receiver ||
					parcel._member_callback == p._member_callback ||
					parcel._lonely_callback == p._lonely_callback ){
					//sameParcelFound = true;
					parcelFound = true;
						//Notice decremented after it is passed to erase() but befor erase() is executed
					list.erase(pIt--);
				}

			}//for
		}
	}//for

	if (!subjectFound || !parcelFound){
		return false;
	}
	else{
		return true;
	}
}

#define Call_Member_Fn(object, ptr) ((object).*(ptr))
void EventManager::_emit(void* subject, const Event& event){

	bool subjectFound = false;
	bool parcelFound = false;
		for(auto it = map.begin(); it != map.end(); ++it){
		const void* __subject = it->first;
		if(subject == __subject){
			subjectFound = true;
			List& list = it->second;
			//bool sameParcelFound = false;
			for(auto pIt = list.begin(); pIt != list.end(); ++pIt){
				Parcel& parcel = *pIt;

				if(parcel._member_callback){

				}

			}//for list
		}
	}//for map

}

