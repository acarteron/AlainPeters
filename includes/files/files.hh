/**
 * \class Files
 *
 * \brief Read Write files
 *
 * \note nothing to add
 *
 * \author $Author: Adrien Carteron$
 *
 * \version $Revision: 1.0 $
 *
 * \date $Date: 2014/07/11 $
 *
 * Contact: acarteron@openmailbox.org
 *
 * Created on: 2011/04/11
 *
 *
 */
#ifndef FILES_HH
#define FILES_HH

//#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <cstring>
namespace apeters{
  class File{
  private:
    std::string fileName; ///< the file name

    std::string ResRead; ///< the line read

    std::ifstream curentFile; ///< the reading stream
    std::ofstream curentFileO; ///< the writing stream
    std::string openingMode; ///< the opening mode

    /// This method creates the input or output stream
    void create_File();

  public:
    /** \brief Void constructor
     * 
     * This only set opening method as in  
     * 
     */
    File();
    /** \brief One arguement constructor
     * \param file name as string
     * 
     * Set opening mode as in
     * set file name calling method setFileName  
     *
     */
    File(std::string);
    /** \brief Two arguement constructor
     * \param file name as string, opening mode as string
     * 
     * Set opening mode
     * set file name calling method setFileName  
     *
     */
    File(std::string,std::string);
    /** \brief Destructor
     * 
     * Close the file 
     *
     */
    ~File();
    /** \brief Method to set file name
     * \param file name as string
     *
     */
    void setFileName(std::string);
    /** \brief Two arguement constructor
     * \param file name as string, opening mode as string
     * 
     * Set opening mode
     * set file name calling method setFileName  
     *
     */
    int openFile();
    int closeFile();
    std::string readFile();
    std::string readLine();
    int writeFile(std::string);

  };
}
#endif
