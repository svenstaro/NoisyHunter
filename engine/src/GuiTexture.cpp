#include "GuiTexture.hpp"

namespace Engine {

GuiTexture::GuiTexture() {}

void GuiTexture::LoadLayoutFile(const std::string& filename) {
/*	boost::property_tree::ptree pt;
	read_info(filename, pt);

	BOOST_FOREACH(boost::property_tree::ptree::value_type& vt, pt.get_child("")) {
		mName = vt.first;
		BOOST_FOREACH(boost::property_tree::ptree::value_type &i, pt.get_child(mName)) {
			std::string image_key = i.first;
			BOOST_FOREACH(boost::property_tree::ptree::value_type &e, pt.get_child(mName + "." + image_key)) {
				std::string element_key = e.first;
				BOOST_FOREACH(boost::property_tree::ptree::value_type &s, pt.get_child(mName + "." + image_key + "." + element_key)) {
					std::string state_key = s.first;
					Logger::Critical(LogOrigin::GUI, "Found Element Key: " + element_key+ "." + state_key);
				}
			}

		}

		exit(0);
	}*/
}

sf::Sprite GuiTexture::GetTextureForKey(const std::string& key) const {

}

const std::string& GuiTexture::GetName() const {
	return mName+"nameolol";
}

}
