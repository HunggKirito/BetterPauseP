#include "pch.h"
#include "Utils.h"


const char* Utils::getNameObj(cocos2d::CCNode* obj) {
	return (typeid(*obj).name() + 6);
}

GameManager* Utils::shareManager() { return GameManager::sharedState(); }
PlayLayer* Utils::getplayLayerA() { return shareManager()->getPlayLayer(); }
cocos2d::CCDirector* Utils::shareDirectorA() { return cocos2d::CCDirector::sharedDirector(); }
cocos2d::CCSize Utils::winSize() { return shareDirectorA()->getWinSize(); }
GLubyte Utils::convertOpacitySimplf(float opaTM) { return SCAST(GLubyte, (255 * opaTM)); }
FMODAudioEngine* Utils::shareFMOD() { return FMODAudioEngine::sharedEngine(); }
GJBaseGameLayer* Utils::getGJBaseGameLayer() {
	return Utils::getplayLayerA() ? static_cast<GJBaseGameLayer*>(Utils::getplayLayerA())
		: static_cast<GJBaseGameLayer*>(Utils::shareManager()->getEditorLayer());
}

//PlayLayer
cocos2d::ccColor3B Utils::primaryIndex() { return shareManager()->colorForIdx(shareManager()->getPlayerColor()); }
cocos2d::ccColor3B Utils::secondaryIndex() { return shareManager()->colorForIdx(shareManager()->getPlayerColor2()); }

float Utils::getPercentagePerXpos() {
	return (getplayLayerA()->m_player1->getPositionX() / getplayLayerA()->m_levelLength * 100.f);
}

float Utils::getPercentageReversePerXpos() {
	return (getplayLayerA()->m_levelLength - getplayLayerA()->m_player1->getPositionX()) / getplayLayerA()->m_levelLength * 100;
}

float Utils::getPercentageNow() {
	//if (sharedStateA().a_percentageViaTimeB) {
		//return Utils::getPercentagePerTime();
	//}
	return Utils::getPercentagePerXpos();
}
float Utils::getPercentageReverseNow() {
	//if (sharedStateA().a_percentageViaTimeB) {
		//return Utils::getPercentageReversePerTime();
	//}
	return Utils::getPercentageReversePerXpos();
}
float Utils::getPercentageNowFix() { return std::min(getPercentageNow(), 100.f); }
float Utils::getPercentageReverseNowFix() { return std::max(getPercentageReverseNow(), 0.f); }

cocos2d::ccColor3B Utils::shiftHue(cocos2d::ccColor3B& color, int shift, int max, int min) {
	if (static_cast<int>(color.r) == max && static_cast<int>(color.g) != max && static_cast<int>(color.b) == min) {
		color.g += shift;
	}
	else if (static_cast<int>(color.r) != min && static_cast<int>(color.g) == max && static_cast<int>(color.b) == min) {
		color.r -= shift;
	}
	else if (static_cast<int>(color.r) == min && static_cast<int>(color.g) == max && static_cast<int>(color.b) != max) {
		color.b += shift;
	}
	else if (static_cast<int>(color.r) == min && static_cast<int>(color.g) != min && static_cast<int>(color.b) == max) {
		color.g -= shift;
	}
	else if (static_cast<int>(color.r) != max && static_cast<int>(color.g) == min && static_cast<int>(color.b) == max) {
		color.r += shift;
	}
	else if (static_cast<int>(color.r) == max && static_cast<int>(color.g) == min && static_cast<int>(color.b) != min) {
		color.b -= shift;
	}
	return color;
}

cocos2d::CCSequence* Utils::rainbowInit(float duration) {
	return cocos2d::CCSequence::create(
		cocos2d::CCTintTo::create(duration, 255, 0, 0),
		cocos2d::CCTintTo::create(duration, 255, 255, 0),
		cocos2d::CCTintTo::create(duration, 0, 255, 0),
		cocos2d::CCTintTo::create(duration, 0, 255, 255),
		cocos2d::CCTintTo::create(duration, 0, 0, 255),
		cocos2d::CCTintTo::create(duration, 255, 0, 255), nullptr
	);
}

cocos2d::CCSequence* Utils::rainbowPastelInit(float duration) {
	return cocos2d::CCSequence::create(
		cocos2d::CCTintTo::create(duration, 255, 201, 222),
		cocos2d::CCTintTo::create(duration, 253, 217, 124),
		cocos2d::CCTintTo::create(duration, 251, 253, 170),
		cocos2d::CCTintTo::create(duration, 193, 240, 178),
		cocos2d::CCTintTo::create(duration, 178, 228, 240),
		cocos2d::CCTintTo::create(duration, 214, 178, 240), nullptr
	);
}

void Utils::ResetColorAndStopRainbow(cocos2d::CCNodeRGBA*& obj, cocos2d::_ccColor3B color) {
	obj->stopAllActions();
	obj->runAction(cocos2d::CCTintTo::create(0.f, color.r, color.g, color.b));
}

void Utils::RainbowSelectA(bool ranN, bool ranP, cocos2d::CCNodeRGBA* obj, float durationranN, float durationranP, cocos2d::ccColor3B colorReset) {

	if (ranN) obj->runAction(cocos2d::CCRepeatForever::create(rainbowInit(durationranN)));
	else if (ranP) obj->runAction(cocos2d::CCRepeatForever::create(rainbowPastelInit(durationranP)));
	else ResetColorAndStopRainbow(obj, colorReset);

}

std::string Utils::convertChartoString(char* c) {
	std::string tmp = c;
	return tmp;
}

std::string Utils::convertConstChartoString(const char* c) {
	std::string tmp = c;
	return tmp;
}

tm* Utils::getRTimeCurrent() {
	time_t tSac = time(NULL);
	struct tm* tmP = localtime(&tSac);
	return tmP;
}

int Utils::getCheatIndicatorState() {
	return 0;
}

cocos2d::ccColor3B Utils::getcolorCheatNow() {

	cocos2d::ccColor3B colorRet = { 0 , 0 , 0 };

	switch (getCheatIndicatorState())
	{
	case 0: {
		colorRet = { 0, 255, 0 };
		break;
	}
	case 1: {
		colorRet = { 255, 255, 0 };
		break;
	}
	case 2: {
		colorRet = { 255, 165, 0 };
		break;
	}
	case 3: {
		colorRet = { 255, 99, 71 };
		break;
	}
	case 4: {
		colorRet = { 255, 0, 0 };
		break;
	}
	default:
		break;
	}

	return colorRet;
}

float Utils::perStartCallOp(int ret)
{

	if (!Utils::getplayLayerA())return 0.f;
	switch (ret)
	{
	case 0: {
		//return (objsUniversal::PlayLayer_gStartXAPractice / Utils::getplayLayerA()->m_levelLength * 100.f);
		break;
	}
	case 1: {
		//return (objsUniversal::PlayLayer_gStartXATestmode / Utils::getplayLayerA()->m_levelLength * 100.f);
		break;
	}
	default:
		break;
	}
	return 0.f;
}

float Utils::convertXposToPercentage(float xPos) {
	if (!Utils::getplayLayerA())return 0.f;

	return (xPos / Utils::getplayLayerA()->m_levelLength * 100.f);
}


const char* Utils::getCCSwitchIntFloat(const char* txtFloat, const char* txtInt, float nf, bool isAcurr) {
	int SafeDecimal = (int)(std::floor(nf));
	auto ret = isAcurr ? cocos2d::CCString::createWithFormat(txtFloat, nf) : cocos2d::CCString::createWithFormat(txtInt, SafeDecimal);
	return ret->getCString();
}

std::string Utils::getPerStrConeAcurr(const char* txt) {
	std::stringstream stream;
	//if (!sharedStateA().a_acurrateP || sharedStateA().a_decimalPS == 0) stream << txt << "%i%%";
	//else stream << txt << "%." << sharedStateA().a_decimalPS << "f%%";
	return stream.str();
}

bool Utils::FindPercentageFixDecimal(char* text) {
	std::string Aux = text;
	if ((Aux.find("%.0f") != std::string::npos) || (Aux.find("%i") != std::string::npos)) return true;
	else return false;
}

std::string Utils::getFontWithFormat(std::uint8_t select) {
	return //objsUniversal::fontNames[select] + 
		".fnt";
}

std::string Utils::getFontWithFormatOriginal(std::uint8_t select) {
	return //objsUniversal::fontNamesOriginal[select] +
		".fnt";
}

int Utils::getMaxZOrdenInLayer(cocos2d::CCLayer* self) {
	cocos2d::CCArray* children = self->getChildren();
	cocos2d::CCObject* child = nullptr;
	int maxZOrder = INT_MIN;
	for (size_t i = 0; i < self->getChildrenCount(); i++)
	{
		auto node = RCAST(cocos2d::CCNode*, child);
		if (node->getZOrder() > maxZOrder)maxZOrder = node->getZOrder();
	}
	return maxZOrder;
}

bool Utils::returnZeroBool(int i) {
	return i == 0;
}

bool Utils::nameChildFind(cocos2d::CCNode* node, const char* name) {
	return Utils::convertConstChartoString(Utils::getNameObj(node)) == name;
}

void Utils::findLayerAndProcessC(bool hide, cocos2d::CCLayer* layer, const char* nameLayer, bool usingLayer) {
	auto scene = Utils::shareDirectorA()->getRunningScene();
	auto childrenCount = usingLayer ? layer->getChildrenCount() : scene->getChildrenCount();
	for (size_t i = 0; i < childrenCount; i++) {
		auto node = geode::cast::typeinfo_cast<cocos2d::CCNode*>(usingLayer ? layer->getChildren()->objectAtIndex(i) : scene->getChildren()->objectAtIndex(i));
		if (node && Utils::nameChildFind(node, nameLayer)) {
			node->setVisible(hide);
		}
	}
}

void Utils::findLayerAndProcessEnabled(bool enabled, cocos2d::CCLayer* layer, const char* nameLayer) {
	auto childrenCount = layer->getChildrenCount();
	for (size_t i = 0; i < childrenCount; i++) {
		auto node = geode::cast::typeinfo_cast<cocos2d::CCMenu*>(layer->getChildren()->objectAtIndex(i));
		if (node && Utils::nameChildFind(node, nameLayer)) {
			node->setEnabled(enabled);
		}
	}
}

void Utils::PlayLayer_getTestModeLabel(PlayLayer* self) {
	if (self->m_isTestMode) {

		auto children = self->getChildren();
		for (int i = 0; i < children->count(); i++) {
			auto child = geode::cast::typeinfo_cast<cocos2d::CCLabelBMFont*>(children->objectAtIndex(i));
			if (child && child->getZOrder() == 1000) {
				auto txtLabel = Utils::convertConstChartoString(child->getString());
				if (!txtLabel.empty() && txtLabel == "Testmode") {
					//objsUniversal::m_labelTestModeA = child;
					break;
				}
			}
		}


	}
}

template <typename T, typename U>
size_t Utils::get_offset(U T::* member)
{
	return reinterpret_cast<char*>(&(((T*)0)->*member)) - reinterpret_cast<char*>(0);
}

cocos2d::CCPoint Utils::getPosLayerLabelsTopButtom(std::uint8_t sel) {
	float y = (sel == 0 || sel == 1) ? Utils::winSize().height - 10.f : 10.f;
	const float baseX = (sel == 0 || sel == 2) ? 3.f : Utils::winSize().width - 3.f;
	float x = baseX;
	cocos2d::CCPoint ret = { x, y };
	return ret;
}

bool Utils::isLabelEmpty(cocos2d::CCLabelProtocol* label) {
	return Utils::convertConstChartoString(label->getString()).empty();
}

std::vector<std::uint8_t> Utils::getPositionAggregatesLabelsA() {
	return { //sharedStateA().a_selectposWinRIMod , sharedStateA().a_selectposWinRIMod , sharedStateA().a_positionBestRunLabel,
		//sharedStateA().a_positionClicksDelayLabel,  sharedStateA().a_positionLastDeadFrameLabel,
		//sharedStateA().a_positionCountDownLabel,  sharedStateA().a_CPSLabelPositionConfig,
		//sharedStateA().a_NCDeathsPositionConfig,  sharedStateA().a_NCALabelPositionConfig,
		//sharedStateA().a_CheatIndLabelPositionConfig, sharedStateA().a_statusDisplayerAPosition
		//,sharedStateA().a_comunLabelStartPosSwitcherPos,
		//sharedStateA().a_coinsViewerPositionLabelConfig, sharedStateA().a_batteryLabelPositionConfig,
		//sharedStateA().a_IDViewerLabelPositionConfig, sharedStateA().a_MessageCustomLabelPositionConfig,
		//sharedStateA().a_hours12timeCurrentPositionConfig, sharedStateA().a_MusicDurationLabelCurrentPositionConfig
	};
}

std::vector<std::uint8_t> Utils::getFntSelectLabelsAggregatesStatusA() {
	return {/* sharedStateA().a_selectfontRIMod, sharedStateA().a_selectfontRIMod,
		sharedStateA().a_BestRunLFontConfig, sharedStateA().a_ClicksDyLabelFontConfig, sharedStateA().a_LDFLabelFontConfig,
		sharedStateA().a_CountDownLabelfontConfig, sharedStateA().a_CPSLabelFontConfig, sharedStateA().a_NCDeathsFontConfig,
		sharedStateA().a_NCALabelFontConfig, sharedStateA().a_CheatIndLabelFontConfig, sharedStateA().a_statusDisplayerAFont
		,sharedStateA().a_universalStartPosSwitcherLabelFontConfig, sharedStateA().a_CoinsViewerFontConfig,
		sharedStateA().a_batteryLabelFontConfig, sharedStateA().a_IDViewerLabelFontConfig, sharedStateA().a_MessageCustomLabelFontConfig,
		sharedStateA().a_hours12timeCurrentLabelFontConfig, sharedStateA().a_MusicDurationLabelCurrentFontConfig,
		*/
	};
}


cocos2d::CCLabelBMFont* Utils::getLabelObjByTag(int tag) {
	if (!Utils::getplayLayerA())return nullptr;
	auto ret = geode::cast::typeinfo_cast<cocos2d::CCLabelBMFont*>(Utils::getplayLayerA()->getChildByTag(tag));
	return ret;
}

char* Utils::convert_to_non_const_char(const char* str) {
	size_t len = std::strlen(str) + 1;
	char* non_const_str = new char[len];
	std::memcpy(non_const_str, str, len);
	return non_const_str;
}

std::string Utils::formatNumberString(std::string format, float firstFloat, float secondFloat) {
	std::stringstream result;
	size_t pos = 0;

	while (pos < format.length()) {
		// buscar el siguiente formato de número
		size_t nextPos = format.find_first_of("%", pos);
		if (nextPos == std::string::npos) {
			// no hay más formatos, agregar el resto de la cadena y salir del ciclo
			result << format.substr(pos);
			break;
		}

		// agregar el texto anterior al formato
		result << format.substr(pos, nextPos - pos);

		// buscar el tipo de formato y procesarlo
		char formatType = format[nextPos + 1];
		if (formatType == 'i') {
			// formato de entero, usar el primer float como entero
			int intValue = static_cast<int>(firstFloat);
			result << intValue;
			// avanzar la posición de búsqueda y actualizar el primer float
			pos = nextPos + 2;
			firstFloat = secondFloat;
		}
		else if (formatType == '.') {
			// formato de flotante, usar el primer float sin conversión
			int precision = 2;
			// buscar la posición del punto
			int decimalPos = format.find(".", nextPos);
			// si no hay punto, agregar solo el punto y avanzar la posición de búsqueda
			if (decimalPos == std::string::npos) {
				result << '.';
				pos = nextPos + 2;
				firstFloat = secondFloat;
			}
			else {
				// buscar el primer carácter no numérico después del punto
				int endPos = format.find_first_not_of("0123456789", decimalPos + 1);
				if (endPos == std::string::npos || format[endPos] != 'f') {
					// si no se encuentra una f después de los números, agregar solo el punto y avanzar la posición de búsqueda
					result << '.';
					pos = nextPos + 2;
					firstFloat = secondFloat;
				}
				else {
					// si se encuentra una f después de los números, procesar el flotante
					std::string precisionStr = format.substr(decimalPos + 1, endPos - decimalPos - 1);
					precision = geode::utils::numFromString<int>(precisionStr).unwrapOr(2);
					result << std::fixed << std::setprecision(precision) << firstFloat;
					// avanzar la posición de búsqueda y actualizar el primer float
					pos = endPos + 1;
					firstFloat = secondFloat;
				}
			}
		}
		else if (formatType == '%') {
			// formato de carácter %, agregar un solo carácter %
			result << '%';
			// avanzar la posición de búsqueda
			pos = nextPos + 2;
		}
		else {
			// formato desconocido, agregar el caracter %
			result << '%';
			// avanzar la posición de búsqueda
			pos = nextPos + 1;
		}
	}

	return result.str();
}

std::string Utils::getVehicleStateString(PlayerObject* player) {
	if (player->m_isShip) {
		return "Ship";
	}
	else if (player->m_isBird) {
		return "UFO";
	}
	else if (player->m_isBall) {
		return "Ball";
	}
	else if (player->m_isDart) {
		return "Wave";
	}
	else if (player->m_isRobot) {
		return "Robot";
	}
	else if (player->m_isSpider) {
		return "Spider";
	}
	else {
		return "Cube";
	}
}


std::string Utils::rgbToHex(int r, int g, int b) {
	std::stringstream stream;
	stream << std::hex << std::setw(2) << std::setfill('0') << r
		<< std::hex << std::setw(2) << std::setfill('0') << g
		<< std::hex << std::setw(2) << std::setfill('0') << b;
	return stream.str();
}

void Utils::hexToRgb(std::string hexValue, float& r, float& g, float& b) {
	std::string hexValueT = hexValue;
	if (hexValueT[0] == '#') {
		// Si la cadena comienza con "#", eliminarlo
		hexValueT.erase(0, 1);
	}
	int intValue = stoi(hexValueT, nullptr, 16);
	r = static_cast<float>((intValue >> 16) & 0xFF);
	g = static_cast<float>((intValue >> 8) & 0xFF);
	b = static_cast<float>(intValue & 0xFF);
	// Verificar que los valores estén en el rango correcto
	if (r < 0.0f) {
		r = 0.0f;
	}
	else if (r > 255.0f) {
		r = 255.0f;
	}
	if (g < 0.0f) {
		g = 0.0f;
	}
	else if (g > 255.0f) {
		g = 255.0f;
	}
	if (b < 0.0f) {
		b = 0.0f;
	}
	else if (b > 255.0f) {
		b = 255.0f;
	}
}


void Utils::rgbToHexForAggregates(int i) {
}

void Utils::hexToRgbForAggregates(int i) {

}

const char* Utils::getDifficultyIcon(GJGameLevel* level) {
	switch (level->m_stars) {
	case 1:
		if (level->m_difficulty == GJDifficulty::Easy) {
			return "difficulty_01_btn_001.png";
		}
		return "difficulty_auto_btn_001.png";
	case 2:
		return "difficulty_01_btn_001.png";
	case 3:
		return "difficulty_02_btn_001.png";
	case 4:
	case 5:
		return "difficulty_03_btn_001.png";
	case 6:
	case 7:
		return "difficulty_04_btn_001.png";
	case 8:
	case 9:
		return "difficulty_05_btn_001.png";
	case 10:
		switch (level->m_demonDifficulty)
		{
		case 3:
			return "difficulty_07_btn_001.png";
		case 4:
			return "difficulty_08_btn_001.png";
		case 5:
			return "difficulty_09_btn_001.png";
		case 6:
			return "difficulty_10_btn_001.png";
		default:
			return "difficulty_06_btn_001.png";
		}
	default:
		return "difficulty_00_btn_001.png";
	}
}

bool Utils::isObjectInVector(const std::vector<std::pair<GameObject*, cocos2d::CCPoint>>& vec, GameObject* obj) {
	for (const auto& p : vec) {
		if (p.first == obj) {
			return true;
		}
	}
	return false;
}

bool Utils::isObjectInVector(const std::vector<std::pair<StartPosObject*, cocos2d::CCPoint>>& vec, GameObject* obj) {
	for (const auto& p : vec) {
		if (p.first == obj) {
			return true;
		}
	}
	return false;
}
