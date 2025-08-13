#include "ResourceLoader.h"

#include "gtengine/utils/types.h"
#include "gtengine/utils/Log.h"

#include <QImage>


#include <QFile>
#include <QTextStream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

namespace gt
{
    ResourceLoader::ResourceLoader(Platform&) { }

    OpResult ResourceLoader::load(Resource::Name name, gref<Texture>& texture)
    {
        std::string prefix(":/resources/");
        std::string fullPath = prefix.append(name);

        auto img = QImage(fullPath.c_str());
        const uchar* data = img.constBits();
        if (!data && !texture->fallback()) {
            FAIL_OP("Texture '%s' not found", name);
        }

        return texture->fill(data, img.width(), img.height(), GL_BGRA);
    }







// ---------- Helper: parse key=value tokens ----------
static std::map<std::string,std::string> parseKeyValues(const std::string &line) {
    std::map<std::string,std::string> out;
    std::istringstream ss(line);
    std::string token;
    // first token is a tag like "info", skip it
    if (!(ss >> token)) return out;
    while (ss >> token) {
        size_t eq = token.find('=');
        if (eq != std::string::npos) {
            std::string key = token.substr(0, eq);
            std::string val = token.substr(eq+1);
            // handle quoted values with spaces
            if (!val.empty() && val.front() == '"') {
                while (val.size() < 2 || val.back() != '"') {
                    std::string extra;
                    if (!(ss >> extra)) break;
                    val += " " + extra;
                }
                if (val.size() >= 2 && val.front() == '"' && val.back() == '"') {
                    val = val.substr(1, val.size()-2);
                }
            }
            out[key] = val;
        }
    }
    return out;
}

// ---------- Parser ----------
bool loadBMFontText(const std::string &fntPath, gref<Font>& font)
{
    QFile resourceFile(fntPath.c_str());
    if (!resourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Error: Could not open Qt resource." << std::endl;
        // Handle error
        return false;
    }

    QTextStream qin(&resourceFile);
    QString content = qin.readAll();
    resourceFile.close(); // Close the QFile once content is read


//    std::ifstream in(fntPath.c_str());
//    if (!in) {
//        std::cerr << "Failed to open: " << fntPath << std::endl;
//        return false;
//    }

    std::stringstream in;
    in << content.toStdString();

    // extract directory for page filenames
    std::string dir;
    size_t pos = fntPath.find_last_of("/\\");
    if (pos != std::string::npos) dir = fntPath.substr(0, pos+1);

    std::string line;
    while (std::getline(in, line)) {
        if (line.compare(0, 7, "common ") == 0) {
            std::map<std::string,std::string> kv = parseKeyValues(line);
            font->lineHeight = std::stoi(kv["lineHeight"]);
            font->base = std::stoi(kv["base"]);
            font->scaleW = std::stoi(kv["scaleW"]);
            font->scaleH = std::stoi(kv["scaleH"]);
        }
        else if (line.compare(0, 5, "page ") == 0) {
            std::map<std::string,std::string> kv = parseKeyValues(line);
            font->pages.push_back(dir + kv["file"]);
        }
        else if (line.compare(0, 5, "char ") == 0) {
            std::map<std::string,std::string> kv = parseKeyValues(line);
            Glyph g;
            g.id = std::stoi(kv["id"]);
            g.x = std::stoi(kv["x"]);
            g.y = std::stoi(kv["y"]);
            g.width = std::stoi(kv["width"]);
            g.height = std::stoi(kv["height"]);
            g.xoffset = std::stoi(kv["xoffset"]);
            g.yoffset = std::stoi(kv["yoffset"]);
            g.xadvance = std::stoi(kv["xadvance"]);
            g.page = kv.count("page") ? std::stoi(kv["page"]) : 0;
            font->glyphs[g.id] = g;
        }
        else if (line.compare(0, 8, "kerning ") == 0) {
            std::map<std::string,std::string> kv = parseKeyValues(line);
            int first = std::stoi(kv["first"]);
            int second = std::stoi(kv["second"]);
            int amount = std::stoi(kv["amount"]);
            font->kernings[std::make_pair(first, second)] = amount;
        }
    }
    return true;
}


    OpResult ResourceLoader::load(Resource::Name name, gref<Font>& font)
    {

        std::string prefix(":/resources/");
        std::string filename = prefix.append(name);

//        std::string filename = "myfont.fnt"; // change to your .fnt file
//        BitmapFont font;

        if (!loadBMFontText(filename, font)) {
            std::cerr << "Error: could not load font file.\n";
            return OpResult::FAIL;
        }

        std::cout << "Loaded font:\n";
        std::cout << " lineHeight = " << font->lineHeight << "\n";
        std::cout << " base = " << font->base << "\n";
        std::cout << " scaleW = " << font->scaleW << "\n";
        std::cout << " scaleH = " << font->scaleH << "\n";

        std::cout << "Pages:\n";
        for (size_t i = 0; i < font->pages.size(); ++i) {
            std::cout << " [" << i << "] " << font->pages[i] << "\n";
        }

        std::cout << "\nFirst 5 glyphs:\n";
        int count = 0;
        for (std::map<int,Glyph>::const_iterator it = font->glyphs.begin(); it != font->glyphs.end() && count < 5; ++it, ++count) {
            const Glyph &g = it->second;
            std::cout << " id=" << g.id
                      << " pos=(" << g.x << "," << g.y << ")"
                      << " size=(" << g.width << "x" << g.height << ")"
                      << " xoff=" << g.xoffset
                      << " yoff=" << g.yoffset
                      << " xadv=" << g.xadvance
                      << " page=" << g.page << "\n";
        }

        std::cout << "\nFirst 5 kerning pairs:\n";
        count = 0;
        for (std::map<std::pair<int,int>,int>::const_iterator it = font->kernings.begin();
             it != font->kernings.end() && count < 5; ++it, ++count) {
            std::cout << " (" << it->first.first << "," << it->first.second << ") -> " << it->second << "\n";
        }



        return OpResult::OK;
    }
}
